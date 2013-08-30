<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.5.0">
<drawing>
<settings>
<setting alwaysvectorfont="yes"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="50" name="dxf" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="14" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="53" name="tGND_GNDA" color="7" fill="9" visible="no" active="no"/>
<layer number="54" name="bGND_GNDA" color="1" fill="9" visible="no" active="no"/>
<layer number="56" name="wert" color="7" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="100" name="Muster" color="7" fill="1" visible="no" active="no"/>
<layer number="101" name="Patch_Top" color="12" fill="4" visible="no" active="yes"/>
<layer number="102" name="Vscore" color="7" fill="1" visible="no" active="yes"/>
<layer number="103" name="tMap" color="7" fill="1" visible="no" active="yes"/>
<layer number="104" name="Name" color="16" fill="1" visible="no" active="yes"/>
<layer number="105" name="tPlate" color="7" fill="1" visible="no" active="yes"/>
<layer number="106" name="bPlate" color="7" fill="1" visible="no" active="yes"/>
<layer number="107" name="Crop" color="7" fill="1" visible="no" active="yes"/>
<layer number="116" name="Patch_BOT" color="9" fill="4" visible="no" active="yes"/>
<layer number="121" name="_tsilk" color="7" fill="1" visible="no" active="yes"/>
<layer number="122" name="_bsilk" color="7" fill="1" visible="no" active="yes"/>
<layer number="125" name="_tNames" color="7" fill="1" visible="no" active="yes"/>
<layer number="144" name="Drill_legend" color="7" fill="1" visible="no" active="yes"/>
<layer number="151" name="HeatSink" color="7" fill="1" visible="no" active="yes"/>
<layer number="200" name="200bmp" color="1" fill="10" visible="no" active="yes"/>
<layer number="201" name="201bmp" color="2" fill="10" visible="no" active="yes"/>
<layer number="202" name="202bmp" color="3" fill="10" visible="no" active="yes"/>
<layer number="203" name="203bmp" color="4" fill="10" visible="no" active="yes"/>
<layer number="204" name="204bmp" color="5" fill="10" visible="no" active="yes"/>
<layer number="205" name="205bmp" color="6" fill="10" visible="no" active="yes"/>
<layer number="206" name="206bmp" color="7" fill="10" visible="no" active="yes"/>
<layer number="207" name="207bmp" color="8" fill="10" visible="no" active="yes"/>
<layer number="208" name="208bmp" color="9" fill="10" visible="no" active="yes"/>
<layer number="209" name="209bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="210" name="210bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="211" name="211bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="212" name="212bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="213" name="213bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="214" name="214bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="215" name="215bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="216" name="216bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="217" name="217bmp" color="18" fill="1" visible="no" active="no"/>
<layer number="218" name="218bmp" color="19" fill="1" visible="no" active="no"/>
<layer number="219" name="219bmp" color="20" fill="1" visible="no" active="no"/>
<layer number="220" name="220bmp" color="21" fill="1" visible="no" active="no"/>
<layer number="221" name="221bmp" color="22" fill="1" visible="no" active="no"/>
<layer number="222" name="222bmp" color="23" fill="1" visible="no" active="no"/>
<layer number="223" name="223bmp" color="24" fill="1" visible="no" active="no"/>
<layer number="224" name="224bmp" color="25" fill="1" visible="no" active="no"/>
<layer number="250" name="Descript" color="3" fill="1" visible="no" active="no"/>
<layer number="251" name="SMDround" color="12" fill="11" visible="no" active="no"/>
<layer number="254" name="cooling" color="7" fill="1" visible="no" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="Teensy3.0">
<packages>
<package name="TEENSY_3.0_ALLPINS">
<pad name="GND" x="-7.62" y="16.51" drill="0.9652"/>
<pad name="0" x="-7.62" y="13.97" drill="0.9652"/>
<pad name="1" x="-7.62" y="11.43" drill="0.9652"/>
<pad name="2" x="-7.62" y="8.89" drill="0.9652"/>
<pad name="3" x="-7.62" y="6.35" drill="0.9652"/>
<pad name="4" x="-7.62" y="3.81" drill="0.9652"/>
<pad name="5" x="-7.62" y="1.27" drill="0.9652"/>
<pad name="6" x="-7.62" y="-1.27" drill="0.9652"/>
<pad name="7" x="-7.62" y="-3.81" drill="0.9652"/>
<pad name="8" x="-7.62" y="-6.35" drill="0.9652"/>
<pad name="9" x="-7.62" y="-8.89" drill="0.9652"/>
<pad name="10" x="-7.62" y="-11.43" drill="0.9652"/>
<pad name="11" x="-7.62" y="-13.97" drill="0.9652"/>
<pad name="12" x="-7.62" y="-16.51" drill="0.9652"/>
<pad name="VBAT" x="-5.08" y="-16.51" drill="0.9652"/>
<pad name="3.3V1" x="-2.54" y="-16.51" drill="0.9652"/>
<pad name="GND1" x="0" y="-16.51" drill="0.9652"/>
<pad name="PGM" x="2.54" y="-16.51" drill="0.9652"/>
<pad name="RESET" x="5.08" y="-16.51" drill="0.9652"/>
<pad name="13" x="7.62" y="-16.51" drill="0.9652"/>
<pad name="14/A0" x="7.62" y="-13.97" drill="0.9652"/>
<pad name="15/A1" x="7.62" y="-11.43" drill="0.9652"/>
<pad name="16/A2" x="7.62" y="-8.89" drill="0.9652"/>
<pad name="17/A3" x="7.62" y="-6.35" drill="0.9652"/>
<pad name="18/A4" x="7.62" y="-3.81" drill="0.9652"/>
<pad name="19/A5" x="7.62" y="-1.27" drill="0.9652"/>
<pad name="20/A6" x="7.62" y="1.27" drill="0.9652"/>
<pad name="21/A7" x="7.62" y="3.81" drill="0.9652"/>
<pad name="22/A8" x="7.62" y="6.35" drill="0.9652"/>
<pad name="23/A9" x="7.62" y="8.89" drill="0.9652"/>
<pad name="3.3V" x="7.62" y="11.43" drill="0.9652"/>
<pad name="AGND" x="7.62" y="13.97" drill="0.9652"/>
<pad name="VIN" x="7.62" y="16.51" drill="0.9652"/>
<wire x1="-8.89" y1="17.78" x2="8.89" y2="17.78" width="0.127" layer="51"/>
<wire x1="8.89" y1="17.78" x2="8.89" y2="-17.78" width="0.127" layer="51"/>
<wire x1="8.89" y1="-17.78" x2="-8.89" y2="-17.78" width="0.127" layer="51"/>
<wire x1="-8.89" y1="-17.78" x2="-8.89" y2="17.78" width="0.127" layer="51"/>
<wire x1="-1.27" y1="16.51" x2="1.27" y2="16.51" width="0.2032" layer="21"/>
<wire x1="1.27" y1="16.51" x2="1.27" y2="17.78" width="0.2032" layer="21"/>
<wire x1="1.27" y1="17.78" x2="8.89" y2="17.78" width="0.2032" layer="21"/>
<wire x1="8.89" y1="17.78" x2="8.89" y2="-17.78" width="0.2032" layer="21"/>
<wire x1="8.89" y1="-17.78" x2="-8.89" y2="-17.78" width="0.2032" layer="21"/>
<wire x1="-8.89" y1="-17.78" x2="-8.89" y2="17.78" width="0.2032" layer="21"/>
<wire x1="-8.89" y1="17.78" x2="-1.27" y2="17.78" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="17.78" x2="-1.27" y2="16.51" width="0.2032" layer="21"/>
<text x="-3.81" y="13.97" size="1.27" layer="25" font="vector">&gt;NAME</text>
<text x="-3.81" y="5.08" size="1.27" layer="27" font="vector">&gt;VALUE</text>
<pad name="VUSB" x="5.08" y="13.97" drill="0.9652"/>
<pad name="AREF" x="5.08" y="8.89" drill="0.9652"/>
<pad name="A10" x="5.08" y="6.35" drill="0.9652"/>
<pad name="A11" x="5.08" y="3.81" drill="0.9652"/>
<pad name="28" x="0" y="-13.97" drill="0.9652"/>
<pad name="29" x="2.54" y="-13.97" drill="0.9652"/>
<pad name="27" x="0" y="-11.43" drill="0.9652"/>
<pad name="26" x="0" y="-8.89" drill="0.9652"/>
<pad name="25" x="0" y="-6.35" drill="0.9652"/>
<pad name="24" x="0" y="-3.81" drill="0.9652"/>
<pad name="30" x="2.54" y="-11.43" drill="0.9652"/>
<pad name="31" x="2.54" y="-8.89" drill="0.9652"/>
<pad name="32" x="2.54" y="-6.35" drill="0.9652"/>
<pad name="33" x="2.54" y="-3.81" drill="0.9652"/>
<pad name="3.3V2" x="2.54" y="-1.27" drill="0.9652"/>
<pad name="A13" x="2.54" y="1.27" drill="0.9652"/>
<pad name="GND2" x="0" y="-1.27" drill="0.9652"/>
<pad name="A12" x="0" y="1.27" drill="0.9652"/>
</package>
<package name="TEENSY_3.0_ALLPINS-SMD">
<wire x1="-8.89" y1="19.05" x2="8.89" y2="19.05" width="0.127" layer="51"/>
<wire x1="8.89" y1="19.05" x2="8.89" y2="-16.51" width="0.127" layer="51"/>
<wire x1="8.89" y1="-16.51" x2="-8.89" y2="-16.51" width="0.127" layer="51"/>
<wire x1="-8.89" y1="-16.51" x2="-8.89" y2="19.05" width="0.127" layer="51"/>
<wire x1="-1.27" y1="17.78" x2="1.27" y2="17.78" width="0.2032" layer="21"/>
<wire x1="1.27" y1="17.78" x2="1.27" y2="19.05" width="0.2032" layer="21"/>
<wire x1="1.27" y1="19.05" x2="8.89" y2="19.05" width="0.2032" layer="21"/>
<wire x1="8.89" y1="19.05" x2="8.89" y2="-16.51" width="0.2032" layer="21"/>
<wire x1="8.89" y1="-16.51" x2="-8.89" y2="-16.51" width="0.2032" layer="21"/>
<wire x1="-8.89" y1="-16.51" x2="-8.89" y2="19.05" width="0.2032" layer="21"/>
<wire x1="-8.89" y1="19.05" x2="-1.27" y2="19.05" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="19.05" x2="-1.27" y2="17.78" width="0.2032" layer="21"/>
<text x="-3.81" y="15.24" size="1.27" layer="25" font="vector">&gt;NAME</text>
<text x="-3.81" y="6.35" size="1.27" layer="27" font="vector">&gt;VALUE</text>
<smd name="A12" x="-1.27" y="2.54" dx="3.556" dy="1.397" layer="1"/>
<smd name="GND2" x="-1.27" y="0" dx="3.556" dy="1.397" layer="1"/>
<smd name="24" x="-1.27" y="-2.54" dx="3.556" dy="1.397" layer="1"/>
<smd name="25" x="-1.27" y="-5.08" dx="3.556" dy="1.397" layer="1"/>
<smd name="26" x="-1.27" y="-7.62" dx="3.556" dy="1.397" layer="1"/>
<smd name="27" x="-1.27" y="-10.16" dx="3.556" dy="1.397" layer="1"/>
<smd name="28" x="-1.27" y="-12.7" dx="3.556" dy="1.397" layer="1"/>
<smd name="29" x="3.81" y="-12.7" dx="3.556" dy="1.397" layer="1"/>
<smd name="30" x="3.81" y="-10.16" dx="3.556" dy="1.397" layer="1"/>
<smd name="31" x="3.81" y="-7.62" dx="3.556" dy="1.397" layer="1"/>
<smd name="32" x="3.81" y="-5.08" dx="3.556" dy="1.397" layer="1"/>
<smd name="33" x="3.81" y="-2.54" dx="3.556" dy="1.397" layer="1"/>
<smd name="3.3V2" x="3.81" y="0" dx="3.556" dy="1.397" layer="1"/>
<smd name="A13" x="3.81" y="2.54" dx="3.556" dy="1.397" layer="1"/>
<smd name="GND" x="-7.62" y="17.78" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="0" x="-7.62" y="15.24" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="1" x="-7.62" y="12.7" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="2" x="-7.62" y="10.16" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="3" x="-7.62" y="7.62" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="4" x="-7.62" y="5.08" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="5" x="-7.62" y="2.54" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="6" x="-7.62" y="0" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="7" x="-7.62" y="-2.54" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="8" x="-7.62" y="-5.08" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="9" x="-7.62" y="-7.62" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="10" x="-7.62" y="-10.16" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="11" x="-7.62" y="-12.7" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="12" x="-7.62" y="-15.24" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="VBAT" x="-5.08" y="-15.24" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="3.3V1" x="-2.54" y="-15.24" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="GND1" x="0" y="-15.24" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="PGM" x="2.54" y="-15.24" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="RESET" x="5.08" y="-15.24" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="13" x="7.62" y="-15.24" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="14/A0" x="7.62" y="-12.7" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="15/A1" x="7.62" y="-10.16" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="16/A2" x="7.62" y="-7.62" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="17/A3" x="7.62" y="-5.08" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="18/A4" x="7.62" y="-2.54" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="19/A5" x="7.62" y="0" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="20/A6" x="7.62" y="2.54" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="21/A7" x="7.62" y="5.08" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="22/A8" x="7.62" y="7.62" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="23/A9" x="7.62" y="10.16" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="3.3V" x="7.62" y="12.7" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="AGND" x="7.62" y="15.24" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="VIN" x="7.62" y="17.78" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="VUSB" x="5.08" y="15.24" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="AREF" x="5.08" y="10.16" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="A10" x="5.08" y="7.62" dx="1.524" dy="1.524" layer="1" roundness="100"/>
<smd name="A11" x="5.08" y="5.08" dx="1.524" dy="1.524" layer="1" roundness="100"/>
</package>
</packages>
<symbols>
<symbol name="TEENSY_3.0_ALLPINS">
<wire x1="-10.16" y1="-35.56" x2="17.78" y2="-35.56" width="0.254" layer="94"/>
<wire x1="17.78" y1="-35.56" x2="17.78" y2="33.02" width="0.254" layer="94"/>
<wire x1="17.78" y1="33.02" x2="-10.16" y2="33.02" width="0.254" layer="94"/>
<wire x1="-10.16" y1="33.02" x2="-10.16" y2="-35.56" width="0.254" layer="94"/>
<pin name="12/MISO" x="-15.24" y="-2.54" visible="pin" length="middle"/>
<pin name="11/MOSI" x="-15.24" y="0" visible="pin" length="middle"/>
<pin name="10/TX2/CS0/PWM" x="-15.24" y="2.54" visible="pin" length="middle"/>
<pin name="9/RX2/CS1/PWM" x="-15.24" y="5.08" visible="pin" length="middle"/>
<pin name="8/TX3" x="-15.24" y="7.62" visible="pin" length="middle"/>
<pin name="7/RX3" x="-15.24" y="10.16" visible="pin" length="middle"/>
<pin name="6/PWM" x="-15.24" y="12.7" visible="pin" length="middle"/>
<pin name="5/PWM" x="-15.24" y="15.24" visible="pin" length="middle"/>
<pin name="4/PWM" x="-15.24" y="17.78" visible="pin" length="middle"/>
<pin name="3/PWM" x="-15.24" y="20.32" visible="pin" length="middle"/>
<pin name="2" x="-15.24" y="22.86" visible="pin" length="middle"/>
<pin name="1/TX1" x="-15.24" y="25.4" visible="pin" length="middle"/>
<pin name="0/RX1" x="-15.24" y="27.94" visible="pin" length="middle"/>
<pin name="GND" x="22.86" y="20.32" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="VIN" x="22.86" y="27.94" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="AGND" x="22.86" y="5.08" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="3.3V" x="22.86" y="25.4" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="23/A9/PWM" x="22.86" y="-10.16" visible="pin" length="middle" rot="R180"/>
<pin name="22/A8/PWM" x="22.86" y="-12.7" visible="pin" length="middle" rot="R180"/>
<pin name="21/A7/CS3/PWM" x="22.86" y="-15.24" visible="pin" length="middle" rot="R180"/>
<pin name="20/A6/CS2/PWM" x="22.86" y="-17.78" visible="pin" length="middle" rot="R180"/>
<pin name="19/A5/SCL" x="22.86" y="-20.32" visible="pin" length="middle" rot="R180"/>
<pin name="18/A4/SDA" x="22.86" y="-22.86" visible="pin" length="middle" rot="R180"/>
<pin name="17/A3" x="22.86" y="-25.4" visible="pin" length="middle" rot="R180"/>
<pin name="16/A2" x="22.86" y="-27.94" visible="pin" length="middle" rot="R180"/>
<pin name="15/A1/CS4" x="22.86" y="-30.48" visible="pin" length="middle" rot="R180"/>
<pin name="14/A0" x="22.86" y="-33.02" visible="pin" length="middle" rot="R180"/>
<pin name="13/SCK/LED" x="-15.24" y="-5.08" visible="pin" length="middle"/>
<pin name="RESET" x="22.86" y="15.24" visible="pin" length="middle" rot="R180"/>
<pin name="PGM" x="22.86" y="12.7" visible="pin" length="middle" rot="R180"/>
<pin name="VBAT" x="22.86" y="22.86" visible="pin" length="middle" direction="pwr" rot="R180"/>
<text x="-3.048" y="34.29" size="1.27" layer="95" font="vector" ratio="15">&gt;NAME</text>
<pin name="A10" x="22.86" y="-7.62" visible="pin" length="middle" rot="R180"/>
<pin name="A11" x="22.86" y="-5.08" visible="pin" length="middle" rot="R180"/>
<pin name="AREF" x="22.86" y="7.62" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="VUSB" x="22.86" y="30.48" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="24" x="-15.24" y="-7.62" visible="pin" length="middle"/>
<pin name="25" x="-15.24" y="-10.16" visible="pin" length="middle"/>
<pin name="26" x="-15.24" y="-12.7" visible="pin" length="middle"/>
<pin name="27" x="-15.24" y="-15.24" visible="pin" length="middle"/>
<pin name="28" x="-15.24" y="-17.78" visible="pin" length="middle"/>
<pin name="29" x="-15.24" y="-20.32" visible="pin" length="middle"/>
<pin name="30" x="-15.24" y="-22.86" visible="pin" length="middle"/>
<pin name="31" x="-15.24" y="-25.4" visible="pin" length="middle"/>
<pin name="32" x="-15.24" y="-27.94" visible="pin" length="middle"/>
<pin name="33" x="-15.24" y="-30.48" visible="pin" length="middle"/>
<pin name="A12" x="22.86" y="-2.54" visible="pin" length="middle" rot="R180"/>
<pin name="A13" x="22.86" y="0" visible="pin" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="TEENSY_3.0_ALLPINS">
<description>Teensy 3.0 with all pin holes and optional SMD-mount unshrouded header on bottom of Teensy 3.0. &lt;p&gt;For more basic versions, see 'Basic', '+4' and 'AllAnalogPins'.&lt;p&gt;Requires the installation of a un-shrouded SMD header on the underside of the Teensy 3.0</description>
<gates>
<gate name="G$1" symbol="TEENSY_3.0_ALLPINS" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TEENSY_3.0_ALLPINS">
<connects>
<connect gate="G$1" pin="0/RX1" pad="0"/>
<connect gate="G$1" pin="1/TX1" pad="1"/>
<connect gate="G$1" pin="10/TX2/CS0/PWM" pad="10"/>
<connect gate="G$1" pin="11/MOSI" pad="11"/>
<connect gate="G$1" pin="12/MISO" pad="12"/>
<connect gate="G$1" pin="13/SCK/LED" pad="13"/>
<connect gate="G$1" pin="14/A0" pad="14/A0"/>
<connect gate="G$1" pin="15/A1/CS4" pad="15/A1"/>
<connect gate="G$1" pin="16/A2" pad="16/A2"/>
<connect gate="G$1" pin="17/A3" pad="17/A3"/>
<connect gate="G$1" pin="18/A4/SDA" pad="18/A4"/>
<connect gate="G$1" pin="19/A5/SCL" pad="19/A5"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="20/A6/CS2/PWM" pad="20/A6"/>
<connect gate="G$1" pin="21/A7/CS3/PWM" pad="21/A7"/>
<connect gate="G$1" pin="22/A8/PWM" pad="22/A8"/>
<connect gate="G$1" pin="23/A9/PWM" pad="23/A9"/>
<connect gate="G$1" pin="24" pad="24"/>
<connect gate="G$1" pin="25" pad="25"/>
<connect gate="G$1" pin="26" pad="26"/>
<connect gate="G$1" pin="27" pad="27"/>
<connect gate="G$1" pin="28" pad="28"/>
<connect gate="G$1" pin="29" pad="29"/>
<connect gate="G$1" pin="3.3V" pad="3.3V 3.3V1 3.3V2"/>
<connect gate="G$1" pin="3/PWM" pad="3"/>
<connect gate="G$1" pin="30" pad="30"/>
<connect gate="G$1" pin="31" pad="31"/>
<connect gate="G$1" pin="32" pad="32"/>
<connect gate="G$1" pin="33" pad="33"/>
<connect gate="G$1" pin="4/PWM" pad="4"/>
<connect gate="G$1" pin="5/PWM" pad="5"/>
<connect gate="G$1" pin="6/PWM" pad="6"/>
<connect gate="G$1" pin="7/RX3" pad="7"/>
<connect gate="G$1" pin="8/TX3" pad="8"/>
<connect gate="G$1" pin="9/RX2/CS1/PWM" pad="9"/>
<connect gate="G$1" pin="A10" pad="A10"/>
<connect gate="G$1" pin="A11" pad="A11"/>
<connect gate="G$1" pin="A12" pad="A12"/>
<connect gate="G$1" pin="A13" pad="A13"/>
<connect gate="G$1" pin="AGND" pad="AGND"/>
<connect gate="G$1" pin="AREF" pad="AREF"/>
<connect gate="G$1" pin="GND" pad="GND GND1 GND2"/>
<connect gate="G$1" pin="PGM" pad="PGM"/>
<connect gate="G$1" pin="RESET" pad="RESET"/>
<connect gate="G$1" pin="VBAT" pad="VBAT"/>
<connect gate="G$1" pin="VIN" pad="VIN"/>
<connect gate="G$1" pin="VUSB" pad="VUSB"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="TEENSY_3.0_ALLPINS-SMD" package="TEENSY_3.0_ALLPINS-SMD">
<connects>
<connect gate="G$1" pin="0/RX1" pad="0"/>
<connect gate="G$1" pin="1/TX1" pad="1"/>
<connect gate="G$1" pin="10/TX2/CS0/PWM" pad="10"/>
<connect gate="G$1" pin="11/MOSI" pad="11"/>
<connect gate="G$1" pin="12/MISO" pad="12"/>
<connect gate="G$1" pin="13/SCK/LED" pad="13"/>
<connect gate="G$1" pin="14/A0" pad="14/A0"/>
<connect gate="G$1" pin="15/A1/CS4" pad="15/A1"/>
<connect gate="G$1" pin="16/A2" pad="16/A2"/>
<connect gate="G$1" pin="17/A3" pad="17/A3"/>
<connect gate="G$1" pin="18/A4/SDA" pad="18/A4"/>
<connect gate="G$1" pin="19/A5/SCL" pad="19/A5"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="20/A6/CS2/PWM" pad="20/A6"/>
<connect gate="G$1" pin="21/A7/CS3/PWM" pad="21/A7"/>
<connect gate="G$1" pin="22/A8/PWM" pad="22/A8"/>
<connect gate="G$1" pin="23/A9/PWM" pad="23/A9"/>
<connect gate="G$1" pin="24" pad="24"/>
<connect gate="G$1" pin="25" pad="25"/>
<connect gate="G$1" pin="26" pad="26"/>
<connect gate="G$1" pin="27" pad="27"/>
<connect gate="G$1" pin="28" pad="28"/>
<connect gate="G$1" pin="29" pad="29"/>
<connect gate="G$1" pin="3.3V" pad="3.3V 3.3V1 3.3V2"/>
<connect gate="G$1" pin="3/PWM" pad="3"/>
<connect gate="G$1" pin="30" pad="30"/>
<connect gate="G$1" pin="31" pad="31"/>
<connect gate="G$1" pin="32" pad="32"/>
<connect gate="G$1" pin="33" pad="33"/>
<connect gate="G$1" pin="4/PWM" pad="4"/>
<connect gate="G$1" pin="5/PWM" pad="5"/>
<connect gate="G$1" pin="6/PWM" pad="6"/>
<connect gate="G$1" pin="7/RX3" pad="7"/>
<connect gate="G$1" pin="8/TX3" pad="8"/>
<connect gate="G$1" pin="9/RX2/CS1/PWM" pad="9"/>
<connect gate="G$1" pin="A10" pad="A10"/>
<connect gate="G$1" pin="A11" pad="A11"/>
<connect gate="G$1" pin="A12" pad="A12"/>
<connect gate="G$1" pin="A13" pad="A13"/>
<connect gate="G$1" pin="AGND" pad="AGND"/>
<connect gate="G$1" pin="AREF" pad="AREF"/>
<connect gate="G$1" pin="GND" pad="GND GND1 GND2"/>
<connect gate="G$1" pin="PGM" pad="PGM"/>
<connect gate="G$1" pin="RESET" pad="RESET"/>
<connect gate="G$1" pin="VBAT" pad="VBAT"/>
<connect gate="G$1" pin="VIN" pad="VIN"/>
<connect gate="G$1" pin="VUSB" pad="VUSB"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SparkFun-Passives">
<description>&lt;h3&gt;SparkFun Electronics' preferred foot prints&lt;/h3&gt;
In this library you'll find resistors, capacitors, inductors, test points, jumper pads, etc.&lt;br&gt;&lt;br&gt;
We've spent an enormous amount of time creating and checking these footprints and parts, but it is the end user's responsibility to ensure correctness and suitablity for a given componet or application. If you enjoy using this library, please buy one of our products at www.sparkfun.com.
&lt;br&gt;&lt;br&gt;
&lt;b&gt;Licensing:&lt;/b&gt; CC v3.0 Share-Alike You are welcome to use this library for commercial purposes. For attribution, we ask that when you begin to sell your device using our footprint, you email us with a link to the product being sold. We want bragging rights that we helped (in a very small part) to create your 8th world wonder. We would like the opportunity to feature your device on our homepage.</description>
<packages>
<package name="PAD.02X.02">
<smd name="P$1" x="0" y="0" dx="0.508" dy="0.508" layer="1"/>
</package>
<package name="PAD.03X.03">
<smd name="P$1" x="0" y="0" dx="0.762" dy="0.762" layer="1" roundness="100" cream="no"/>
</package>
<package name="PAD.03X.05">
<smd name="P$1" x="0" y="0" dx="1.27" dy="1.27" layer="1" roundness="100" cream="no"/>
</package>
</packages>
<symbols>
<symbol name="TEST-POINT">
<wire x1="2.54" y1="0" x2="0" y2="0" width="0.1524" layer="94"/>
<wire x1="3.302" y1="0.762" x2="3.302" y2="-0.762" width="0.1524" layer="94" curve="180"/>
<text x="-2.54" y="2.54" size="1.778" layer="95">&gt;Name</text>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;Value</text>
<pin name="1" x="0" y="0" visible="off" length="point" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="TEST-POINT" prefix="TP">
<description>Bare copper test points for troubleshooting or ICT</description>
<gates>
<gate name="G$1" symbol="TEST-POINT" x="0" y="0"/>
</gates>
<devices>
<device name="2" package="PAD.02X.02">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3" package="PAD.03X.03">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3X5" package="PAD.03X.05">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U$1" library="Teensy3.0" deviceset="TEENSY_3.0_ALLPINS" device="TEENSY_3.0_ALLPINS-SMD"/>
<part name="TP1" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP2" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP3" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP4" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP5" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP6" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP7" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP8" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP9" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP10" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP11" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP12" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP13" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP14" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP15" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP16" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP17" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP18" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP19" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP20" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP21" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP22" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP23" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP24" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP25" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP26" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP27" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP28" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP29" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP30" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP31" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP32" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP33" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP34" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP35" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP36" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP37" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP38" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP39" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP40" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP41" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP42" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP43" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP44" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP45" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP46" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP47" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP48" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP49" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP50" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
<part name="TP51" library="SparkFun-Passives" deviceset="TEST-POINT" device="3"/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="20.32" y="43.18"/>
<instance part="TP1" gate="G$1" x="5.08" y="71.12" rot="R180"/>
<instance part="TP2" gate="G$1" x="5.08" y="68.58" rot="R180"/>
<instance part="TP3" gate="G$1" x="5.08" y="66.04" rot="R180"/>
<instance part="TP4" gate="G$1" x="5.08" y="63.5" rot="R180"/>
<instance part="TP5" gate="G$1" x="5.08" y="60.96" rot="R180"/>
<instance part="TP6" gate="G$1" x="5.08" y="58.42" rot="R180"/>
<instance part="TP7" gate="G$1" x="5.08" y="55.88" rot="R180"/>
<instance part="TP8" gate="G$1" x="5.08" y="53.34" rot="R180"/>
<instance part="TP9" gate="G$1" x="5.08" y="50.8" rot="R180"/>
<instance part="TP10" gate="G$1" x="5.08" y="48.26" rot="R180"/>
<instance part="TP11" gate="G$1" x="5.08" y="45.72" rot="R180"/>
<instance part="TP12" gate="G$1" x="5.08" y="43.18" rot="R180"/>
<instance part="TP13" gate="G$1" x="5.08" y="40.64" rot="R180"/>
<instance part="TP14" gate="G$1" x="5.08" y="38.1" rot="R180"/>
<instance part="TP15" gate="G$1" x="5.08" y="35.56" rot="R180"/>
<instance part="TP16" gate="G$1" x="5.08" y="33.02" rot="R180"/>
<instance part="TP17" gate="G$1" x="5.08" y="30.48" rot="R180"/>
<instance part="TP18" gate="G$1" x="5.08" y="27.94" rot="R180"/>
<instance part="TP19" gate="G$1" x="5.08" y="25.4" rot="R180"/>
<instance part="TP20" gate="G$1" x="5.08" y="22.86" rot="R180"/>
<instance part="TP21" gate="G$1" x="5.08" y="20.32" rot="R180"/>
<instance part="TP22" gate="G$1" x="5.08" y="17.78" rot="R180"/>
<instance part="TP23" gate="G$1" x="5.08" y="15.24" rot="R180"/>
<instance part="TP24" gate="G$1" x="5.08" y="12.7" rot="R180"/>
<instance part="TP25" gate="G$1" x="43.18" y="10.16"/>
<instance part="TP26" gate="G$1" x="43.18" y="12.7"/>
<instance part="TP27" gate="G$1" x="43.18" y="15.24"/>
<instance part="TP28" gate="G$1" x="43.18" y="17.78"/>
<instance part="TP29" gate="G$1" x="43.18" y="20.32"/>
<instance part="TP30" gate="G$1" x="43.18" y="22.86"/>
<instance part="TP31" gate="G$1" x="43.18" y="25.4"/>
<instance part="TP32" gate="G$1" x="43.18" y="27.94"/>
<instance part="TP33" gate="G$1" x="43.18" y="30.48"/>
<instance part="TP34" gate="G$1" x="43.18" y="33.02"/>
<instance part="TP35" gate="G$1" x="43.18" y="35.56"/>
<instance part="TP36" gate="G$1" x="43.18" y="38.1"/>
<instance part="TP37" gate="G$1" x="43.18" y="40.64"/>
<instance part="TP38" gate="G$1" x="43.18" y="43.18"/>
<instance part="TP39" gate="G$1" x="43.18" y="48.26"/>
<instance part="TP40" gate="G$1" x="43.18" y="50.8"/>
<instance part="TP41" gate="G$1" x="43.18" y="55.88"/>
<instance part="TP42" gate="G$1" x="43.18" y="58.42"/>
<instance part="TP43" gate="G$1" x="43.18" y="63.5"/>
<instance part="TP44" gate="G$1" x="43.18" y="66.04"/>
<instance part="TP45" gate="G$1" x="43.18" y="68.58"/>
<instance part="TP46" gate="G$1" x="43.18" y="71.12"/>
<instance part="TP47" gate="G$1" x="43.18" y="73.66"/>
<instance part="TP48" gate="G$1" x="76.2" y="71.12"/>
<instance part="TP49" gate="G$1" x="76.2" y="68.58"/>
<instance part="TP50" gate="G$1" x="76.2" y="60.96"/>
<instance part="TP51" gate="G$1" x="76.2" y="58.42"/>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="0/RX1"/>
<pinref part="TP1" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="1/TX1"/>
<pinref part="TP2" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="2"/>
<pinref part="TP3" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="3/PWM"/>
<pinref part="TP4" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="4/PWM"/>
<pinref part="TP5" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="5/PWM"/>
<pinref part="TP6" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="6/PWM"/>
<pinref part="TP7" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="7/RX3"/>
<pinref part="TP8" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="8/TX3"/>
<pinref part="TP9" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="9/RX2/CS1/PWM"/>
<pinref part="TP10" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="10/TX2/CS0/PWM"/>
<pinref part="TP11" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="11/MOSI"/>
<pinref part="TP12" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="12/MISO"/>
<pinref part="TP13" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="13/SCK/LED"/>
<pinref part="TP14" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="24"/>
<pinref part="TP15" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="25"/>
<pinref part="TP16" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$17" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="26"/>
<pinref part="TP17" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$18" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="27"/>
<pinref part="TP18" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$19" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="28"/>
<pinref part="TP19" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$20" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="29"/>
<pinref part="TP20" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$21" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="30"/>
<pinref part="TP21" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$22" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="31"/>
<pinref part="TP22" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$23" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="32"/>
<pinref part="TP23" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$24" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="33"/>
<pinref part="TP24" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$25" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="14/A0"/>
<pinref part="TP25" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$26" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="15/A1/CS4"/>
<pinref part="TP26" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$27" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="16/A2"/>
<pinref part="TP27" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$28" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="17/A3"/>
<pinref part="TP28" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$29" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="18/A4/SDA"/>
<pinref part="TP29" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$30" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="19/A5/SCL"/>
<pinref part="TP30" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$31" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="20/A6/CS2/PWM"/>
<pinref part="TP31" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$32" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="21/A7/CS3/PWM"/>
<pinref part="TP32" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$33" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="22/A8/PWM"/>
<pinref part="TP33" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$34" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="23/A9/PWM"/>
<pinref part="TP34" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$35" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="A10"/>
<pinref part="TP35" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$36" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="A11"/>
<pinref part="TP36" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$37" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="A12"/>
<pinref part="TP37" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$38" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="A13"/>
<pinref part="TP38" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$39" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="AGND"/>
<pinref part="TP39" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$40" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="AREF"/>
<pinref part="TP40" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$41" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="PGM"/>
<pinref part="TP41" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$42" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="RESET"/>
<pinref part="TP42" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$44" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="VBAT"/>
<pinref part="TP44" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$46" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="VIN"/>
<pinref part="TP46" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$47" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="VUSB"/>
<pinref part="TP47" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$48" class="0">
<segment>
<pinref part="TP49" gate="G$1" pin="1"/>
<wire x1="76.2" y1="68.58" x2="71.12" y2="68.58" width="0.1524" layer="91"/>
<wire x1="71.12" y1="68.58" x2="71.12" y2="71.12" width="0.1524" layer="91"/>
<pinref part="TP48" gate="G$1" pin="1"/>
<wire x1="71.12" y1="71.12" x2="76.2" y2="71.12" width="0.1524" layer="91"/>
<wire x1="71.12" y1="71.12" x2="60.96" y2="71.12" width="0.1524" layer="91"/>
<wire x1="60.96" y1="71.12" x2="60.96" y2="68.58" width="0.1524" layer="91"/>
<junction x="71.12" y="71.12"/>
<pinref part="U$1" gate="G$1" pin="3.3V"/>
<pinref part="TP45" gate="G$1" pin="1"/>
<wire x1="60.96" y1="68.58" x2="43.18" y2="68.58" width="0.1524" layer="91"/>
<junction x="43.18" y="68.58"/>
</segment>
</net>
<net name="N$45" class="0">
<segment>
<pinref part="TP51" gate="G$1" pin="1"/>
<wire x1="76.2" y1="58.42" x2="73.66" y2="58.42" width="0.1524" layer="91"/>
<wire x1="73.66" y1="58.42" x2="73.66" y2="60.96" width="0.1524" layer="91"/>
<pinref part="TP50" gate="G$1" pin="1"/>
<wire x1="73.66" y1="60.96" x2="76.2" y2="60.96" width="0.1524" layer="91"/>
<wire x1="73.66" y1="60.96" x2="73.66" y2="63.5" width="0.1524" layer="91"/>
<junction x="73.66" y="60.96"/>
<pinref part="U$1" gate="G$1" pin="GND"/>
<pinref part="TP43" gate="G$1" pin="1"/>
<wire x1="73.66" y1="63.5" x2="43.18" y2="63.5" width="0.1524" layer="91"/>
<junction x="43.18" y="63.5"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
