# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  ipgui::add_param $IPINST -name "C_DATA_TDATA_WIDTH" -parent ${Page_0} -widget comboBox
  ipgui::add_param $IPINST -name "C_CONTROL_DATA_WIDTH" -parent ${Page_0} -widget comboBox
  ipgui::add_param $IPINST -name "C_CONTROL_ADDR_WIDTH" -parent ${Page_0}
  ipgui::add_param $IPINST -name "C_CONTROL_BASEADDR" -parent ${Page_0}
  ipgui::add_param $IPINST -name "C_CONTROL_HIGHADDR" -parent ${Page_0}


}

proc update_PARAM_VALUE.C_DATA_TDATA_WIDTH { PARAM_VALUE.C_DATA_TDATA_WIDTH } {
	# Procedure called to update C_DATA_TDATA_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_DATA_TDATA_WIDTH { PARAM_VALUE.C_DATA_TDATA_WIDTH } {
	# Procedure called to validate C_DATA_TDATA_WIDTH
	return true
}

proc update_PARAM_VALUE.C_CONTROL_DATA_WIDTH { PARAM_VALUE.C_CONTROL_DATA_WIDTH } {
	# Procedure called to update C_CONTROL_DATA_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_CONTROL_DATA_WIDTH { PARAM_VALUE.C_CONTROL_DATA_WIDTH } {
	# Procedure called to validate C_CONTROL_DATA_WIDTH
	return true
}

proc update_PARAM_VALUE.C_CONTROL_ADDR_WIDTH { PARAM_VALUE.C_CONTROL_ADDR_WIDTH } {
	# Procedure called to update C_CONTROL_ADDR_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_CONTROL_ADDR_WIDTH { PARAM_VALUE.C_CONTROL_ADDR_WIDTH } {
	# Procedure called to validate C_CONTROL_ADDR_WIDTH
	return true
}

proc update_PARAM_VALUE.C_CONTROL_BASEADDR { PARAM_VALUE.C_CONTROL_BASEADDR } {
	# Procedure called to update C_CONTROL_BASEADDR when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_CONTROL_BASEADDR { PARAM_VALUE.C_CONTROL_BASEADDR } {
	# Procedure called to validate C_CONTROL_BASEADDR
	return true
}

proc update_PARAM_VALUE.C_CONTROL_HIGHADDR { PARAM_VALUE.C_CONTROL_HIGHADDR } {
	# Procedure called to update C_CONTROL_HIGHADDR when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_CONTROL_HIGHADDR { PARAM_VALUE.C_CONTROL_HIGHADDR } {
	# Procedure called to validate C_CONTROL_HIGHADDR
	return true
}


proc update_MODELPARAM_VALUE.C_DATA_TDATA_WIDTH { MODELPARAM_VALUE.C_DATA_TDATA_WIDTH PARAM_VALUE.C_DATA_TDATA_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_DATA_TDATA_WIDTH}] ${MODELPARAM_VALUE.C_DATA_TDATA_WIDTH}
}

proc update_MODELPARAM_VALUE.C_CONTROL_DATA_WIDTH { MODELPARAM_VALUE.C_CONTROL_DATA_WIDTH PARAM_VALUE.C_CONTROL_DATA_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_CONTROL_DATA_WIDTH}] ${MODELPARAM_VALUE.C_CONTROL_DATA_WIDTH}
}

proc update_MODELPARAM_VALUE.C_CONTROL_ADDR_WIDTH { MODELPARAM_VALUE.C_CONTROL_ADDR_WIDTH PARAM_VALUE.C_CONTROL_ADDR_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_CONTROL_ADDR_WIDTH}] ${MODELPARAM_VALUE.C_CONTROL_ADDR_WIDTH}
}

