#include "cy22393.h"
#include "i2c.h"
#include "types.h"

// FPLL = Fref * Pt / Qt
// Qt = Q + 2
// Pt = (2 * (P + 3)) + PO

result_t cy22393_init (I2C_BUS bus_id, u8 dev_addr)
{
    // Source select
    i2c_write_reg(bus_id, dev_addr, 0x0E, 0x02); // ClkD, ClkC, ClkB, ClkA: Ref Clk

    // Clock Adjustments
    i2c_write_reg(bus_id, dev_addr, 0x0F, 0x50); // Nominal duty cycles, Xbuf output enabled
    i2c_write_reg(bus_id, dev_addr, 0x10, 0x55); // Nominal output drive strengthes

    // Oscillator settings
    i2c_write_reg(bus_id, dev_addr, 0x17, 0x03); // Oscillator capacitance 6pF + OscDrv for external ref clock 27MHz

    // PLL1 configuration
    i2c_write_reg(bus_id, dev_addr, 0x40, 0x06); // when S='000'
    i2c_write_reg(bus_id, dev_addr, 0x41, 0x05);
    i2c_write_reg(bus_id, dev_addr, 0x42, 0x40);

    // PLL2 configuration
    i2c_write_reg(bus_id, dev_addr, 0x11, 0x06); // Qt = 2
    i2c_write_reg(bus_id, dev_addr, 0x12, 0x05); // Pt = 0
    i2c_write_reg(bus_id, dev_addr, 0x13, 0x40);

    // PLL3 configuration
    i2c_write_reg(bus_id, dev_addr, 0x14, 0x00); // Qt = 2
    i2c_write_reg(bus_id, dev_addr, 0x15, 0x00); // Pt = 0
    i2c_write_reg(bus_id, dev_addr, 0x16, 0x00); // Fpll3 = Fref * Pt/Qt = 297 Mhz

    // Clock dividers
    i2c_write_reg(bus_id, dev_addr, 0x08, 100); // ClkA Divider when DivSel low, In-Phase
    i2c_write_reg(bus_id, dev_addr, 0x09, 0x00); // ClkA Divider when DivSel high (unused)
    i2c_write_reg(bus_id, dev_addr, 0x0A, 0x00); // ClkB Divider when DivSel low, In-Phase
    i2c_write_reg(bus_id, dev_addr, 0x0B, 0x00); // ClkB Divider when DivSel high (unused)
    i2c_write_reg(bus_id, dev_addr, 0x0C, 0x00); // ClkC Divider, In-Phase
    i2c_write_reg(bus_id, dev_addr, 0x0D, 0x00); // ClkD Divider, In-Phase
}
