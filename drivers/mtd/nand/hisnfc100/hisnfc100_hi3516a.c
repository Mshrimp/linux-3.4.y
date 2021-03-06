/******************************************************************************
*    Copyright (c) 2014 by Hisilicon.
*    All rights reserved.
******************************************************************************/

#include "hisnfc100_os.h"
#include "hisnfc100.h"

/*****************************************************************************/
#define HISNFC100_CRG48					0xc0
#define HISNFC100_CRG48_SPI_NAND_CLK_SEL(_clk)		(((_clk) & 0x3) << 6)
#define HISNFC100_CRG48_SPI_NAND_CLK_EN			(1 << 5)
#define HISNFC100_CRG48_SPI_NAND_SOFT_RST_REQ		(1 << 4)

#define SPI_NAND_CLK_SEL_MASK				(0x3 << 6)

#define CLK_24M						0
#define CLK_75M						1
#define CLK_125M					2

#define SPI_NAND_CLK_SEL_24M	HISNFC100_CRG48_SPI_NAND_CLK_SEL(CLK_24M)
#define SPI_NAND_CLK_SEL_75M	HISNFC100_CRG48_SPI_NAND_CLK_SEL(CLK_75M)
#define SPI_NAND_CLK_SEL_125M	HISNFC100_CRG48_SPI_NAND_CLK_SEL(CLK_125M)

/*****************************************************************************/
void hisnfc100_set_system_clock(struct spi_op_info *op, int clk_en)
{
	unsigned int base = IO_ADDRESS(CRG_REG_BASE);
	unsigned int regval, old_val;

	old_val = regval = readl(base + HISNFC100_CRG48);

	regval &= ~SPI_NAND_CLK_SEL_MASK;

	if (op && op->clock)
		regval |= op->clock &  SPI_NAND_CLK_SEL_MASK;
	else
		regval |= SPI_NAND_CLK_SEL_24M;

	if (clk_en)
		regval |= HISNFC100_CRG48_SPI_NAND_CLK_EN;
	else
		regval &= ~HISNFC100_CRG48_SPI_NAND_CLK_EN;

	if (regval != old_val)
		writel(regval, (base + HISNFC100_CRG48));
}

/*****************************************************************************/
void hisnfc100_get_best_clock(unsigned int *clock)
{
	int ix;
	int clk_reg;
#define CLK_2X(_clk)	(((_clk) + 1) >> 1)
	unsigned int sysclk[] = {
		CLK_2X(24),	SPI_NAND_CLK_SEL_24M,
		CLK_2X(75),	SPI_NAND_CLK_SEL_75M,
		CLK_2X(125),	SPI_NAND_CLK_SEL_125M,
		0, 0,
	};
#undef CLK_2X

	clk_reg = SPI_NAND_CLK_SEL_24M;
	for (ix = 0; sysclk[ix]; ix += 2) {
		if (*clock < sysclk[ix])
			break;
		clk_reg = sysclk[ix + 1];
	}

	*clock = clk_reg;
}

