# Test-Jig-Common

The MCP23008 is a pretty straight-forward I2C GPIO expander.  It has some registers which you allows you to configure pins as input/output, pull-up/pull-down, etc. And of course other registers you write/clear to set a value, or read from in the case of an input.  I knew I was going to use this bad Larry on a couple different test jigs, so I took the time to create a generic driver that interfaces with ST’s hardware abstraction layer.  

You just create an instance of an MCP23008, initialize it, and then you can read or write whole registers, or to individual pins.  It doesn’t encompass everything, but I feel the way I coded makes it easy to build upon if necessary.
