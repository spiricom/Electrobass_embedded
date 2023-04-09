# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\JeffSnyder\dev\Electrobass_embedded\PSOC5_electrobass_stringsensors\CE210514_PSOC3_5_Thermistor.cydsn\CE210514_PSOC3_5_Thermistor.cyprj
# Date: Sat, 08 Apr 2023 23:34:49 GMT
#set_units -time ns
create_clock -name {ADC_1_Ext_CP_Clk(routed)} -period 12.681159420289854 -waveform {0 6.34057971014493} [list [get_pins {ClockBlock/dclk_0}]]
create_clock -name {ADC_SAR_Seq_1_IntClock(routed)} -period 697.463768115942 -waveform {0 348.731884057971} [list [get_pins {ClockBlock/dclk_4}]]
create_clock -name {CyILO} -period 10000 -waveform {0 5000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 12.681159420289854 -waveform {0 6.34057971014493} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 12.681159420289854 -waveform {0 6.34057971014493} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_clock -name {ADC_1_Ext_CP_Clk} -period 12.681159420289854 -waveform {0 6.34057971014493} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {SPIM_1_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 5 11} -nominal_period 63.405797101449267 [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {SPIM_2_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 5 11} -nominal_period 63.405797101449267 [list [get_pins {ClockBlock/dclk_glb_2}]]
create_generated_clock -name {ADC_1_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 17 33} [list [get_pins {ClockBlock/aclk_glb_0}]]
create_generated_clock -name {ADC_SAR_Seq_1_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 55 111} [list [get_pins {ClockBlock/dclk_glb_4}]]
create_generated_clock -name {CapSense_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 7 13} -nominal_period 83.333333333333329 [list [get_pins {ClockBlock/dclk_glb_3}]]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Users\JeffSnyder\dev\Electrobass_embedded\PSOC5_electrobass_stringsensors\CE210514_PSOC3_5_Thermistor.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\JeffSnyder\dev\Electrobass_embedded\PSOC5_electrobass_stringsensors\CE210514_PSOC3_5_Thermistor.cydsn\CE210514_PSOC3_5_Thermistor.cyprj
# Date: Sat, 08 Apr 2023 23:34:25 GMT
