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
<layer number="21" name="tPlace" color="16" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="14" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="14" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="6" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="0" visible="no" active="no"/>
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
<layer number="51" name="tDocu" color="6" fill="1" visible="no" active="no"/>
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
<layer number="101" name="Patch_Top" color="12" fill="4" visible="yes" active="yes"/>
<layer number="102" name="Vscore" color="7" fill="1" visible="yes" active="yes"/>
<layer number="103" name="tMap" color="7" fill="1" visible="yes" active="yes"/>
<layer number="104" name="Name" color="16" fill="1" visible="yes" active="yes"/>
<layer number="105" name="tPlate" color="7" fill="1" visible="yes" active="yes"/>
<layer number="106" name="bPlate" color="7" fill="1" visible="yes" active="yes"/>
<layer number="107" name="Crop" color="7" fill="1" visible="yes" active="yes"/>
<layer number="108" name="tplace-old" color="10" fill="1" visible="yes" active="yes"/>
<layer number="109" name="ref-old" color="11" fill="1" visible="yes" active="yes"/>
<layer number="116" name="Patch_BOT" color="9" fill="4" visible="yes" active="yes"/>
<layer number="121" name="_tsilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="122" name="_bsilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="125" name="_tNames" color="7" fill="1" visible="yes" active="yes"/>
<layer number="144" name="Drill_legend" color="7" fill="1" visible="yes" active="yes"/>
<layer number="151" name="HeatSink" color="7" fill="1" visible="yes" active="yes"/>
<layer number="199" name="Contour" color="7" fill="1" visible="yes" active="yes"/>
<layer number="200" name="200bmp" color="1" fill="10" visible="yes" active="yes"/>
<layer number="201" name="201bmp" color="2" fill="10" visible="yes" active="yes"/>
<layer number="202" name="202bmp" color="3" fill="10" visible="yes" active="yes"/>
<layer number="203" name="203bmp" color="4" fill="10" visible="yes" active="yes"/>
<layer number="204" name="204bmp" color="5" fill="10" visible="yes" active="yes"/>
<layer number="205" name="205bmp" color="6" fill="10" visible="yes" active="yes"/>
<layer number="206" name="206bmp" color="7" fill="10" visible="yes" active="yes"/>
<layer number="207" name="207bmp" color="8" fill="10" visible="yes" active="yes"/>
<layer number="208" name="208bmp" color="9" fill="10" visible="yes" active="yes"/>
<layer number="209" name="209bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="210" name="210bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="211" name="211bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="212" name="212bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="213" name="213bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="214" name="214bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="215" name="215bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="216" name="216bmp" color="7" fill="1" visible="yes" active="yes"/>
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
<layer number="254" name="cooling" color="7" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="supply1">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="GND">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
<symbol name="+3V3">
<wire x1="1.27" y1="-1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<text x="-2.54" y="-5.08" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="+3V3" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
<symbol name="+5V">
<wire x1="1.27" y1="-1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<text x="-2.54" y="-5.08" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="+5V" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
<symbol name="VCC">
<wire x1="1.27" y1="-1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="VCC" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND" prefix="GND">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="+3V3" prefix="+3V3">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="+3V3" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="+5V" prefix="P+">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="+5V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="VCC" prefix="P+">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="VCC" symbol="VCC" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="My Parts">
<packages>
<package name="8-PIN_RECEPTACLE_LOCK_NO-SS">
<wire x1="-10.16" y1="-1.27" x2="-10.16" y2="1.27" width="0.254" layer="23"/>
<wire x1="-10.16" y1="1.27" x2="10.16" y2="1.27" width="0.254" layer="23"/>
<wire x1="10.16" y1="1.27" x2="10.16" y2="-1.27" width="0.254" layer="23"/>
<wire x1="10.16" y1="-1.27" x2="-10.16" y2="-1.27" width="0.254" layer="23"/>
<pad name="P$1" x="-8.89" y="-0.127" drill="0.8"/>
<pad name="P$2" x="-6.35" y="0.127" drill="0.8"/>
<pad name="P$3" x="-3.81" y="-0.127" drill="0.8"/>
<pad name="P$4" x="-1.27" y="0.127" drill="0.8"/>
<pad name="P$5" x="1.27" y="-0.127" drill="0.8"/>
<pad name="P$6" x="3.81" y="0.127" drill="0.8"/>
<pad name="P$7" x="6.35" y="-0.127" drill="0.8"/>
<pad name="P$8" x="8.89" y="0.127" drill="0.8"/>
</package>
<package name="USB_SOCKET">
<pad name="P$5" x="-6.57" y="0" drill="2.3"/>
<pad name="P$6" x="6.57" y="0" drill="2.3"/>
<pad name="P$1" x="-3.5" y="2.71" drill="0.92"/>
<pad name="P$2" x="-1" y="2.71" drill="0.92"/>
<pad name="P$3" x="1" y="2.71" drill="0.92"/>
<pad name="P$4" x="3.5" y="2.71" drill="0.92"/>
<wire x1="-6.55" y1="3.8" x2="-6.55" y2="-10.3" width="0.254" layer="21"/>
<wire x1="-6.55" y1="-10.3" x2="6.55" y2="-10.3" width="0.254" layer="21"/>
<wire x1="6.55" y1="-10.3" x2="6.55" y2="3.8" width="0.254" layer="21"/>
<wire x1="6.55" y1="3.8" x2="-6.55" y2="3.8" width="0.254" layer="21"/>
<text x="-3.3" y="-7" size="2.54" layer="21">USB</text>
</package>
</packages>
<symbols>
<symbol name="8-PIN_HEADER">
<wire x1="-3.81" y1="-12.7" x2="3.81" y2="-12.7" width="0.4064" layer="94"/>
<wire x1="3.81" y1="-12.7" x2="3.81" y2="10.16" width="0.4064" layer="94"/>
<wire x1="3.81" y1="10.16" x2="-3.81" y2="10.16" width="0.4064" layer="94"/>
<wire x1="-3.81" y1="10.16" x2="-3.81" y2="-12.7" width="0.4064" layer="94"/>
<text x="-3.81" y="10.795" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.81" y="-15.24" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="0" y="7.62" visible="pin" length="short" direction="pas" function="dot"/>
<pin name="2" x="0" y="5.08" visible="pin" length="short" direction="pas" function="dot"/>
<pin name="3" x="0" y="2.54" visible="pin" length="short" direction="pas" function="dot"/>
<pin name="4" x="0" y="0" visible="pin" length="short" direction="pas" function="dot"/>
<pin name="5" x="0" y="-2.54" visible="pin" length="short" direction="pas" function="dot"/>
<pin name="6" x="0" y="-5.08" visible="pin" length="short" direction="pas" function="dot"/>
<pin name="7" x="0" y="-7.62" visible="pin" length="short" direction="pas" function="dot"/>
<pin name="8" x="0" y="-10.16" visible="pin" length="short" direction="pas" function="dot"/>
</symbol>
<symbol name="USB_SOCKET">
<wire x1="5.08" y1="7.62" x2="-2.54" y2="7.62" width="0.254" layer="94"/>
<wire x1="-2.54" y1="7.62" x2="-2.54" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-5.08" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<pin name="D+" x="-5.08" y="5.08" visible="off" length="short"/>
<pin name="D-" x="-5.08" y="2.54" visible="off" length="short"/>
<pin name="VBUS" x="-5.08" y="0" visible="off" length="short"/>
<pin name="GND" x="-5.08" y="-2.54" visible="off" length="short"/>
<pin name="P$1" x="0" y="-7.62" visible="off" length="short" rot="R90"/>
<pin name="P$2" x="2.54" y="-7.62" visible="off" length="short" rot="R90"/>
<text x="-1.27" y="-0.762" size="1.778" layer="94">Vbus</text>
<text x="-1.27" y="-3.556" size="1.778" layer="94">Gnd</text>
<text x="-1.27" y="1.524" size="1.778" layer="94">D-</text>
<text x="-1.27" y="4.318" size="1.778" layer="94">D+</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="8-PIN_HEADER">
<gates>
<gate name="G$1" symbol="8-PIN_HEADER" x="0" y="0"/>
</gates>
<devices>
<device name="" package="8-PIN_RECEPTACLE_LOCK_NO-SS">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
<connect gate="G$1" pin="3" pad="P$3"/>
<connect gate="G$1" pin="4" pad="P$4"/>
<connect gate="G$1" pin="5" pad="P$5"/>
<connect gate="G$1" pin="6" pad="P$6"/>
<connect gate="G$1" pin="7" pad="P$7"/>
<connect gate="G$1" pin="8" pad="P$8"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="USB_SOCKET">
<gates>
<gate name="G$1" symbol="USB_SOCKET" x="0" y="0"/>
</gates>
<devices>
<device name="TYPE-A" package="USB_SOCKET">
<connects>
<connect gate="G$1" pin="D+" pad="P$3"/>
<connect gate="G$1" pin="D-" pad="P$2"/>
<connect gate="G$1" pin="GND" pad="P$4"/>
<connect gate="G$1" pin="P$1" pad="P$5"/>
<connect gate="G$1" pin="P$2" pad="P$6"/>
<connect gate="G$1" pin="VBUS" pad="P$1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="CH_passive">
<packages>
<package name="CRYSTAL-SMD-5X3">
<wire x1="-0.6" y1="1.6" x2="0.6" y2="1.6" width="0.2032" layer="21"/>
<wire x1="2.5" y1="0.3" x2="2.5" y2="-0.3" width="0.2032" layer="21"/>
<wire x1="0.6" y1="-1.6" x2="-0.6" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="0.3" x2="-2.5" y2="-0.3" width="0.2032" layer="21"/>
<smd name="1" x="-1.85" y="-1.15" dx="1.9" dy="1.1" layer="1"/>
<smd name="3" x="1.85" y="1.15" dx="1.9" dy="1.1" layer="1"/>
<smd name="4" x="-1.85" y="1.15" dx="1.9" dy="1.1" layer="1"/>
<smd name="2" x="1.85" y="-1.15" dx="1.9" dy="1.1" layer="1"/>
<text x="-2.54" y="1.905" size="0.4064" layer="25">&gt;NAME</text>
<text x="-2.54" y="-2.54" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="1206">
<wire x1="-2.473" y1="0.983" x2="2.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="2.473" y1="-0.983" x2="-2.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-2.473" y1="-0.983" x2="-2.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="2.473" y1="0.983" x2="2.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-0.965" y1="0.787" x2="0.965" y2="0.787" width="0.1016" layer="51"/>
<wire x1="-0.965" y1="-0.787" x2="0.965" y2="-0.787" width="0.1016" layer="51"/>
<wire x1="-0.2032" y1="0.9144" x2="0.2032" y2="0.9144" width="0.2032" layer="21"/>
<wire x1="0.2032" y1="0.9144" x2="0.2032" y2="-0.9144" width="0.2032" layer="21"/>
<wire x1="0.2032" y1="-0.9144" x2="-0.2032" y2="-0.9144" width="0.2032" layer="21"/>
<wire x1="-0.2032" y1="-0.9144" x2="-0.2032" y2="0.9144" width="0.2032" layer="21"/>
<smd name="1" x="-1.4" y="0" dx="1.6" dy="1.8" layer="1"/>
<smd name="2" x="1.4" y="0" dx="1.6" dy="1.8" layer="1"/>
<text x="-1.27" y="1.143" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.397" y="-1.524" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-1.7018" y1="-0.8509" x2="-0.9517" y2="0.8491" layer="51"/>
<rectangle x1="0.9517" y1="-0.8491" x2="1.7018" y2="0.8509" layer="51"/>
<rectangle x1="-0.1999" y1="-0.4001" x2="0.1999" y2="0.4001" layer="35"/>
</package>
<package name="0603">
<description>&lt;strong&gt;0603&lt;/strong&gt; package</description>
<wire x1="-1.473" y1="0.733" x2="1.473" y2="0.733" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.733" x2="1.473" y2="-0.733" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.733" x2="-1.473" y2="-0.733" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.733" x2="-1.473" y2="0.733" width="0.0508" layer="39"/>
<wire x1="-0.356" y1="0.432" x2="0.356" y2="0.432" width="0.0762" layer="51"/>
<wire x1="-0.356" y1="-0.419" x2="0.356" y2="-0.419" width="0.0762" layer="51"/>
<wire x1="-1.1176" y1="0.8128" x2="1.1176" y2="0.8128" width="0.2032" layer="21"/>
<wire x1="-1.1176" y1="-0.8128" x2="1.1176" y2="-0.8128" width="0.2032" layer="21"/>
<smd name="1" x="-0.85" y="0" dx="1.1" dy="1" layer="1"/>
<smd name="2" x="0.85" y="0" dx="1.1" dy="1" layer="1"/>
<text x="-0.889" y="0.762" size="0.4064" layer="25" font="vector">&gt;NAME</text>
<text x="-1.016" y="-1.143" size="0.4064" layer="27" font="vector">&gt;VALUE</text>
<rectangle x1="-0.8382" y1="-0.4699" x2="-0.3381" y2="0.4801" layer="51"/>
<rectangle x1="0.3302" y1="-0.4699" x2="0.8303" y2="0.4801" layer="51"/>
<rectangle x1="-0.1999" y1="-0.3" x2="0.1999" y2="0.3" layer="35"/>
</package>
<package name="AXIAL-0.3">
<wire x1="-2.54" y1="0.762" x2="2.54" y2="0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0.762" x2="2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0" x2="2.54" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="-0.762" x2="-2.54" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="-0.762" x2="-2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0" x2="2.794" y2="0" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.794" y2="0" width="0.2032" layer="21"/>
<pad name="P$1" x="-3.81" y="0" drill="0.9"/>
<pad name="P$2" x="3.81" y="0" drill="0.9"/>
<text x="-2.54" y="1.27" size="0.4064" layer="25">&gt;Name</text>
<text x="-2.032" y="-0.508" size="0.8128" layer="21">&gt;Value</text>
</package>
<package name="R2010">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;&lt;p&gt;
chip</description>
<wire x1="-1.662" y1="1.245" x2="1.662" y2="1.245" width="0.1524" layer="51"/>
<wire x1="-1.637" y1="-1.245" x2="1.687" y2="-1.245" width="0.1524" layer="51"/>
<wire x1="-3.473" y1="1.483" x2="3.473" y2="1.483" width="0.0508" layer="39"/>
<wire x1="3.473" y1="1.483" x2="3.473" y2="-1.483" width="0.0508" layer="39"/>
<wire x1="3.473" y1="-1.483" x2="-3.473" y2="-1.483" width="0.0508" layer="39"/>
<wire x1="-3.473" y1="-1.483" x2="-3.473" y2="1.483" width="0.0508" layer="39"/>
<wire x1="-1.027" y1="1.245" x2="1.027" y2="1.245" width="0.1524" layer="21"/>
<wire x1="-1.002" y1="-1.245" x2="1.016" y2="-1.245" width="0.1524" layer="21"/>
<smd name="1" x="-2.2" y="0" dx="1.8" dy="2.7" layer="1"/>
<smd name="2" x="2.2" y="0" dx="1.8" dy="2.7" layer="1"/>
<text x="-2.54" y="1.5875" size="0.4064" layer="25">&gt;NAME</text>
<text x="-2.54" y="-2.032" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-2.4892" y1="-1.3208" x2="-1.6393" y2="1.3292" layer="51"/>
<rectangle x1="1.651" y1="-1.3208" x2="2.5009" y2="1.3292" layer="51"/>
</package>
<package name="C0402">
<description>&lt;b&gt;CAPACITOR&lt;/b&gt;&lt;p&gt;
chip</description>
<wire x1="-0.245" y1="0.224" x2="0.245" y2="0.224" width="0.1524" layer="51"/>
<wire x1="0.245" y1="-0.224" x2="-0.245" y2="-0.224" width="0.1524" layer="51"/>
<wire x1="-1.473" y1="0.483" x2="1.473" y2="0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.483" x2="1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.483" x2="-1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.483" x2="-1.473" y2="0.483" width="0.0508" layer="39"/>
<smd name="1" x="-0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<smd name="2" x="0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<text x="-0.889" y="0.6985" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.0795" y="-1.143" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-0.554" y1="-0.3048" x2="-0.254" y2="0.2951" layer="51"/>
<rectangle x1="0.2588" y1="-0.3048" x2="0.5588" y2="0.2951" layer="51"/>
<rectangle x1="-0.1999" y1="-0.3" x2="0.1999" y2="0.3" layer="35"/>
</package>
<package name="0805">
<wire x1="-0.3" y1="0.6" x2="0.3" y2="0.6" width="0.1524" layer="21"/>
<wire x1="-0.3" y1="-0.6" x2="0.3" y2="-0.6" width="0.1524" layer="21"/>
<smd name="1" x="-0.9" y="0" dx="0.8" dy="1.2" layer="1"/>
<smd name="2" x="0.9" y="0" dx="0.8" dy="1.2" layer="1"/>
<text x="-0.762" y="0.8255" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.016" y="-1.397" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="1210">
<description>standard 1210 (3225) package.&lt;br&gt;Pads 1.6x2.7mm, distance between centers 2.8mm</description>
<wire x1="-2.473" y1="1.583" x2="2.473" y2="1.583" width="0.0508" layer="39"/>
<wire x1="2.473" y1="-1.583" x2="-2.473" y2="-1.583" width="0.0508" layer="39"/>
<wire x1="-2.473" y1="-1.583" x2="-2.473" y2="1.583" width="0.0508" layer="39"/>
<wire x1="2.473" y1="1.583" x2="2.473" y2="-1.583" width="0.0508" layer="39"/>
<wire x1="-0.965" y1="1.187" x2="0.965" y2="1.187" width="0.03" layer="51"/>
<wire x1="-0.965" y1="-1.187" x2="0.965" y2="-1.187" width="0.03" layer="51"/>
<smd name="1" x="-1.4" y="0" dx="1.6" dy="2.7" layer="1"/>
<smd name="2" x="1.4" y="0" dx="1.6" dy="2.7" layer="1"/>
<text x="-1.27" y="1.843" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.397" y="-2.224" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-0.1999" y1="-0.4001" x2="0.1999" y2="0.4001" layer="35"/>
<rectangle x1="-1.8" y1="-1.2" x2="-1" y2="1.2" layer="51"/>
<rectangle x1="1" y1="-1.2" x2="1.8" y2="1.2" layer="51"/>
</package>
<package name="CAP-PTH-SMALL">
<wire x1="1.27" y1="0.635" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="0.7"/>
<pad name="2" x="2.54" y="0" drill="0.7"/>
</package>
<package name="CAP-PTH-SMALL2">
<wire x1="1.27" y1="0.635" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="1.27" x2="3.81" y2="1.27" width="0.2032" layer="21"/>
<wire x1="3.81" y1="1.27" x2="3.81" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-1.27" x2="-1.27" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-1.27" x2="-1.27" y2="1.27" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="0.7"/>
<pad name="2" x="2.54" y="0" drill="0.7"/>
</package>
<package name="EIA3216">
<wire x1="-1" y1="-1.2" x2="-2.5" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="-1.2" x2="-2.5" y2="1.2" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="1.2" x2="-1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="1" y1="-1.2" x2="2.1" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="2.1" y1="-1.2" x2="2.5" y2="-0.8" width="0.2032" layer="21"/>
<wire x1="2.5" y1="-0.8" x2="2.5" y2="0.8" width="0.2032" layer="21"/>
<wire x1="2.5" y1="0.8" x2="2.1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="2.1" y1="1.2" x2="1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="-2" y1="1.25" x2="2" y2="1.25" width="0.127" layer="39"/>
<wire x1="2" y1="1.25" x2="2" y2="-1.25" width="0.127" layer="39"/>
<wire x1="2" y1="-1.25" x2="-2" y2="-1.25" width="0.127" layer="39"/>
<wire x1="-2" y1="-1.25" x2="-2" y2="1.25" width="0.127" layer="39"/>
<smd name="C" x="-1.4" y="0" dx="1.6" dy="1.4" layer="1" rot="R90"/>
<smd name="A" x="1.4" y="0" dx="1.6" dy="1.4" layer="1" rot="R90"/>
<text x="-2.54" y="1.381" size="0.4064" layer="25">&gt;NAME</text>
<text x="0.408" y="1.332" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="EIA3528">
<wire x1="-0.9" y1="-1.6" x2="-2.6" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="-1.6" x2="-2.6" y2="1.55" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="1.55" x2="-0.9" y2="1.55" width="0.2032" layer="21"/>
<wire x1="1" y1="-1.55" x2="2.2" y2="-1.55" width="0.2032" layer="21"/>
<wire x1="2.2" y1="-1.55" x2="2.6" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="2.6" y1="-1.2" x2="2.6" y2="1.25" width="0.2032" layer="21"/>
<wire x1="2.6" y1="1.25" x2="2.2" y2="1.55" width="0.2032" layer="21"/>
<wire x1="2.2" y1="1.55" x2="1" y2="1.55" width="0.2032" layer="21"/>
<smd name="C" x="-1.65" y="0" dx="2.5" dy="1.2" layer="1" rot="R90"/>
<smd name="A" x="1.65" y="0" dx="2.5" dy="1.2" layer="1" rot="R90"/>
<text x="-2.27" y="-1.27" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="3.24" y="-1.37" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
</package>
<package name="CPOL-RADIAL-100UF-25V">
<wire x1="-0.635" y1="1.27" x2="-1.905" y2="1.27" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="3.25" width="0.2032" layer="21"/>
<pad name="2" x="-1.27" y="0" drill="0.7"/>
<pad name="1" x="1.27" y="0" drill="0.7" shape="square"/>
</package>
<package name="CPOL-RADIAL-10UF-25V">
<wire x1="-0.645" y1="0.92" x2="-1.915" y2="0.92" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="2.5" width="0.2032" layer="21"/>
<pad name="1" x="1.27" y="0" drill="0.7" shape="square"/>
<pad name="2" x="-1.27" y="0" drill="0.7"/>
</package>
<package name="EIA7343">
<wire x1="-5" y1="2.5" x2="-2" y2="2.5" width="0.2032" layer="21"/>
<wire x1="-5" y1="2.5" x2="-5" y2="-2.5" width="0.2032" layer="21"/>
<wire x1="-5" y1="-2.5" x2="-2" y2="-2.5" width="0.2032" layer="21"/>
<wire x1="2" y1="2.5" x2="4" y2="2.5" width="0.2032" layer="21"/>
<wire x1="4" y1="2.5" x2="5" y2="1.5" width="0.2032" layer="21"/>
<wire x1="5" y1="1.5" x2="5" y2="-1.5" width="0.2032" layer="21"/>
<wire x1="5" y1="-1.5" x2="4" y2="-2.5" width="0.2032" layer="21"/>
<wire x1="4" y1="-2.5" x2="2" y2="-2.5" width="0.2032" layer="21"/>
<smd name="C" x="-3.17" y="0" dx="2.55" dy="2.7" layer="1" rot="R180"/>
<smd name="A" x="3.17" y="0" dx="2.55" dy="2.7" layer="1" rot="R180"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.27" y="-1.27" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="PANASONIC_G">
<description>&lt;b&gt;Panasonic Aluminium Electrolytic Capacitor VS-Serie Package G&lt;/b&gt;</description>
<wire x1="-5.1" y1="5.1" x2="2.8" y2="5.1" width="0.1016" layer="51"/>
<wire x1="2.8" y1="5.1" x2="5.1" y2="2.8" width="0.1016" layer="51"/>
<wire x1="5.1" y1="2.8" x2="5.1" y2="-2.8" width="0.1016" layer="51"/>
<wire x1="5.1" y1="-2.8" x2="2.8" y2="-5.1" width="0.1016" layer="51"/>
<wire x1="2.8" y1="-5.1" x2="-5.1" y2="-5.1" width="0.1016" layer="51"/>
<wire x1="-5.1" y1="-5.1" x2="-5.1" y2="5.1" width="0.1016" layer="51"/>
<wire x1="-5.1" y1="1.635" x2="-5.1" y2="5.1" width="0.2032" layer="21"/>
<wire x1="-5.1" y1="5.1" x2="2.8" y2="5.1" width="0.2032" layer="21"/>
<wire x1="2.8" y1="5.1" x2="5.1" y2="2.8" width="0.2032" layer="21"/>
<wire x1="5.1" y1="2.8" x2="5.1" y2="1.635" width="0.2032" layer="21"/>
<wire x1="5.1" y1="-1.635" x2="5.1" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="5.1" y1="-2.8" x2="2.8" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="2.8" y1="-5.1" x2="-5.1" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="-5.1" y1="-5.1" x2="-5.1" y2="-1.635" width="0.2032" layer="21"/>
<wire x1="-4.85" y1="-1" x2="4.85" y2="-1" width="0.2032" layer="21" curve="156.699401" cap="flat"/>
<wire x1="-4.85" y1="1" x2="4.85" y2="1" width="0.2032" layer="21" curve="-156.699401" cap="flat"/>
<wire x1="-3.25" y1="3.7" x2="-3.25" y2="-3.65" width="0.1016" layer="51"/>
<circle x="0" y="0" radius="4.95" width="0.1016" layer="51"/>
<smd name="-" x="-4.25" y="0" dx="3.9" dy="1.6" layer="1"/>
<smd name="+" x="4.25" y="0" dx="3.9" dy="1.6" layer="1"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="-2.54" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-5.85" y1="-0.45" x2="-4.9" y2="0.45" layer="51"/>
<rectangle x1="4.9" y1="-0.45" x2="5.85" y2="0.45" layer="51"/>
<polygon width="0.1016" layer="51">
<vertex x="-3.3" y="3.6"/>
<vertex x="-4.05" y="2.75"/>
<vertex x="-4.65" y="1.55"/>
<vertex x="-4.85" y="0.45"/>
<vertex x="-4.85" y="-0.45"/>
<vertex x="-4.65" y="-1.55"/>
<vertex x="-4.05" y="-2.75"/>
<vertex x="-3.3" y="-3.6"/>
<vertex x="-3.3" y="3.55"/>
</polygon>
</package>
<package name="PANASONIC_E">
<description>&lt;b&gt;Panasonic Aluminium Electrolytic Capacitor VS-Serie Package E&lt;/b&gt;</description>
<wire x1="-4.1" y1="4.1" x2="1.8" y2="4.1" width="0.1016" layer="51"/>
<wire x1="1.8" y1="4.1" x2="4.1" y2="1.8" width="0.1016" layer="51"/>
<wire x1="4.1" y1="1.8" x2="4.1" y2="-1.8" width="0.1016" layer="51"/>
<wire x1="4.1" y1="-1.8" x2="1.8" y2="-4.1" width="0.1016" layer="51"/>
<wire x1="1.8" y1="-4.1" x2="-4.1" y2="-4.1" width="0.1016" layer="51"/>
<wire x1="-4.1" y1="-4.1" x2="-4.1" y2="4.1" width="0.1016" layer="51"/>
<wire x1="-4.1" y1="0.9" x2="-4.1" y2="4.1" width="0.2032" layer="21"/>
<wire x1="-4.1" y1="4.1" x2="1.8" y2="4.1" width="0.2032" layer="21"/>
<wire x1="1.8" y1="4.1" x2="4.1" y2="1.8" width="0.2032" layer="21"/>
<wire x1="4.1" y1="1.8" x2="4.1" y2="0.9" width="0.2032" layer="21"/>
<wire x1="4.1" y1="-0.9" x2="4.1" y2="-1.8" width="0.2032" layer="21"/>
<wire x1="4.1" y1="-1.8" x2="1.8" y2="-4.1" width="0.2032" layer="21"/>
<wire x1="1.8" y1="-4.1" x2="-4.1" y2="-4.1" width="0.2032" layer="21"/>
<wire x1="-4.1" y1="-4.1" x2="-4.1" y2="-0.9" width="0.2032" layer="21"/>
<wire x1="-2.2" y1="3.25" x2="-2.2" y2="-3.25" width="0.1016" layer="51"/>
<wire x1="-3.85" y1="0.9" x2="3.85" y2="0.9" width="0.2032" layer="21" curve="-153.684915" cap="flat"/>
<wire x1="-3.85" y1="-0.9" x2="3.85" y2="-0.9" width="0.2032" layer="21" curve="153.684915" cap="flat"/>
<circle x="0" y="0" radius="3.95" width="0.1016" layer="51"/>
<smd name="-" x="-3" y="0" dx="3.8" dy="1.4" layer="1"/>
<smd name="+" x="3" y="0" dx="3.8" dy="1.4" layer="1"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="-2.54" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-4.5" y1="-0.35" x2="-3.8" y2="0.35" layer="51"/>
<rectangle x1="3.8" y1="-0.35" x2="4.5" y2="0.35" layer="51"/>
<polygon width="0.1016" layer="51">
<vertex x="-2.25" y="3.2"/>
<vertex x="-3" y="2.5"/>
<vertex x="-3.6" y="1.5"/>
<vertex x="-3.85" y="0.65"/>
<vertex x="-3.85" y="-0.65"/>
<vertex x="-3.55" y="-1.6"/>
<vertex x="-2.95" y="-2.55"/>
<vertex x="-2.25" y="-3.2"/>
<vertex x="-2.25" y="3.15"/>
</polygon>
</package>
</packages>
<symbols>
<symbol name="GND">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
<symbol name="Q_SH">
<wire x1="1.016" y1="0" x2="2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="0" x2="-1.016" y2="0" width="0.1524" layer="94"/>
<wire x1="-0.381" y1="1.524" x2="-0.381" y2="-1.524" width="0.254" layer="94"/>
<wire x1="-0.381" y1="-1.524" x2="0.381" y2="-1.524" width="0.254" layer="94"/>
<wire x1="0.381" y1="-1.524" x2="0.381" y2="1.524" width="0.254" layer="94"/>
<wire x1="0.381" y1="1.524" x2="-0.381" y2="1.524" width="0.254" layer="94"/>
<wire x1="1.016" y1="1.778" x2="1.016" y2="-1.778" width="0.254" layer="94"/>
<wire x1="-1.016" y1="1.778" x2="-1.016" y2="-1.778" width="0.254" layer="94"/>
<wire x1="-1.778" y1="1.905" x2="-1.778" y2="2.54" width="0.1524" layer="94"/>
<wire x1="-1.778" y1="2.54" x2="1.778" y2="2.54" width="0.1524" layer="94"/>
<wire x1="1.778" y1="2.54" x2="1.778" y2="1.905" width="0.1524" layer="94"/>
<wire x1="1.778" y1="-1.905" x2="1.778" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-1.778" y1="-2.54" x2="1.778" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-1.778" y1="-2.54" x2="-1.778" y2="-1.905" width="0.1524" layer="94"/>
<text x="2.54" y="1.016" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<text x="-2.159" y="-1.143" size="0.8636" layer="93">1</text>
<text x="1.524" y="-1.143" size="0.8636" layer="93">2</text>
<text x="1.143" y="2.794" size="0.8636" layer="93" rot="R90">3</text>
<text x="1.27" y="-3.556" size="0.8636" layer="93" rot="R90">4</text>
<pin name="2" x="2.54" y="0" visible="off" length="point" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-2.54" y="0" visible="off" length="point" direction="pas" swaplevel="1"/>
<pin name="3" x="0" y="5.08" visible="off" length="short" direction="pas" rot="R270"/>
<pin name="4" x="0" y="-5.08" visible="off" length="short" direction="pas" rot="R90"/>
</symbol>
<symbol name="RESISTOR">
<wire x1="-2.54" y1="0" x2="-2.159" y2="1.016" width="0.1524" layer="94"/>
<wire x1="-2.159" y1="1.016" x2="-1.524" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="-1.524" y1="-1.016" x2="-0.889" y2="1.016" width="0.1524" layer="94"/>
<wire x1="-0.889" y1="1.016" x2="-0.254" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="-0.254" y1="-1.016" x2="0.381" y2="1.016" width="0.1524" layer="94"/>
<wire x1="0.381" y1="1.016" x2="1.016" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="1.016" y1="-1.016" x2="1.651" y2="1.016" width="0.1524" layer="94"/>
<wire x1="1.651" y1="1.016" x2="2.286" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="2.286" y1="-1.016" x2="2.54" y2="0" width="0.1524" layer="94"/>
<text x="-3.81" y="1.4986" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.81" y="-3.302" size="1.778" layer="96">&gt;VALUE</text>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
</symbol>
<symbol name="CAP">
<wire x1="0" y1="2.54" x2="0" y2="2.032" width="0.1524" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="0.508" width="0.1524" layer="94"/>
<text x="1.524" y="2.921" size="1.778" layer="95">&gt;NAME</text>
<text x="1.524" y="-2.159" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-2.032" y1="0.508" x2="2.032" y2="1.016" layer="94"/>
<rectangle x1="-2.032" y1="1.524" x2="2.032" y2="2.032" layer="94"/>
<pin name="1" x="0" y="5.08" visible="off" length="short" direction="pas" swaplevel="1" rot="R270"/>
<pin name="2" x="0" y="-2.54" visible="off" length="short" direction="pas" swaplevel="1" rot="R90"/>
</symbol>
<symbol name="CAP_POL">
<wire x1="-2.54" y1="0" x2="2.54" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="-1.016" x2="0" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="0" y1="-1" x2="2.4892" y2="-1.8542" width="0.254" layer="94" curve="-37.878202" cap="flat"/>
<wire x1="-2.4669" y1="-1.8504" x2="0" y2="-1.0161" width="0.254" layer="94" curve="-37.376341" cap="flat"/>
<text x="1.016" y="0.635" size="1.778" layer="95">&gt;NAME</text>
<text x="1.016" y="-4.191" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-2.253" y1="0.668" x2="-1.364" y2="0.795" layer="94"/>
<rectangle x1="-1.872" y1="0.287" x2="-1.745" y2="1.176" layer="94"/>
<pin name="+" x="0" y="2.54" visible="off" length="short" direction="pas" swaplevel="1" rot="R270"/>
<pin name="-" x="0" y="-5.08" visible="off" length="short" direction="pas" swaplevel="1" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND" prefix="GND">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="CRYSTAL_SH">
<gates>
<gate name="G$1" symbol="Q_SH" x="0" y="0"/>
</gates>
<devices>
<device name="" package="CRYSTAL-SMD-5X3">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="3"/>
<connect gate="G$1" pin="3" pad="2"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="RESISTOR" prefix="R" uservalue="yes">
<description>&lt;b&gt;Resistor&lt;/b&gt;
Basic schematic elements and footprints for 0603, 1206, and PTH 1/10th watt (small) resistors.</description>
<gates>
<gate name="G$1" symbol="RESISTOR" x="0" y="0"/>
</gates>
<devices>
<device name="1206" package="1206">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0603" package="0603">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH1" package="AXIAL-0.3">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="2010" package="R2010">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0402" package="C0402">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0805" package="0805">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1210" package="1210">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="CAP" prefix="C" uservalue="yes">
<description>&lt;b&gt;Capacitor&lt;/b&gt;
Standard 0603 ceramic capacitor, and 0.1" leaded capacitor.</description>
<gates>
<gate name="G$1" symbol="CAP" x="0" y="0"/>
</gates>
<devices>
<device name="0603" package="0603">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH" package="CAP-PTH-SMALL">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH2" package="CAP-PTH-SMALL2">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0402" package="C0402">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0805" package="0805">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1210" package="1210">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1206" package="1206">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="CAP_POL" prefix="C" uservalue="yes">
<description>&lt;b&gt;Capacitor Polarized&lt;/b&gt;
These are standard SMD and PTH capacitors. Normally 10uF, 47uF, and 100uF in electrolytic and tantalum varieties. Always verify the external diameter of the through hole cap, it varies with capacity, voltage, and manufacturer. The EIA devices should be standard.</description>
<gates>
<gate name="G$1" symbol="CAP_POL" x="0" y="0"/>
</gates>
<devices>
<device name="1206" package="EIA3216">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3528" package="EIA3528">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH1" package="CPOL-RADIAL-100UF-25V">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH2" package="CPOL-RADIAL-10UF-25V">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="7343" package="EIA7343">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="G" package="PANASONIC_G">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="E" package="PANASONIC_E">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="CH_Maxim">
<packages>
<package name="TQFP32_8MIL">
<wire x1="-2.125" y1="4" x2="2.125" y2="4" width="0.0254" layer="39"/>
<wire x1="2.125" y1="4" x2="2.125" y2="2.125" width="0.0254" layer="39"/>
<wire x1="2.125" y1="2.125" x2="4" y2="2.125" width="0.0254" layer="39"/>
<wire x1="4" y1="2.125" x2="4" y2="-2.125" width="0.0254" layer="39"/>
<wire x1="4" y1="-2.125" x2="2.125" y2="-2.125" width="0.0254" layer="39"/>
<wire x1="2.125" y1="-2.125" x2="2.125" y2="-4" width="0.0254" layer="39"/>
<wire x1="-2.125" y1="-2.125" x2="-4" y2="-2.125" width="0.0254" layer="39"/>
<wire x1="-4" y1="-2.125" x2="-4" y2="2.125" width="0.0254" layer="39"/>
<wire x1="-4" y1="2.125" x2="-2.125" y2="2.125" width="0.0254" layer="39"/>
<wire x1="-2.125" y1="2.125" x2="-2.125" y2="4" width="0.0254" layer="39"/>
<wire x1="2.125" y1="-4" x2="-2.125" y2="-4" width="0.0254" layer="39"/>
<wire x1="-2.125" y1="-4" x2="-2.125" y2="-2.125" width="0.0254" layer="39"/>
<wire x1="-2.4" y1="-2.4" x2="2.4" y2="-2.4" width="0.03" layer="51"/>
<wire x1="2.4" y1="-2.4" x2="2.4" y2="2.4" width="0.03" layer="51"/>
<wire x1="2.4" y1="2.4" x2="-2.4" y2="2.4" width="0.03" layer="51"/>
<wire x1="-2.4" y1="2.4" x2="-2.4" y2="-2.4" width="0.03" layer="51"/>
<wire x1="-3.048" y1="-2.3368" x2="-2.3368" y2="-2.3368" width="0.2032" layer="21"/>
<wire x1="-2.3368" y1="-2.3368" x2="-2.3368" y2="-3.048" width="0.2032" layer="21"/>
<wire x1="-2.3368" y1="-3.048" x2="-3.048" y2="-2.3368" width="0.2032" layer="21"/>
<wire x1="2.3368" y1="-3.048" x2="3.048" y2="-3.048" width="0.2032" layer="21"/>
<wire x1="3.048" y1="-3.048" x2="3.048" y2="-2.3368" width="0.2032" layer="21"/>
<wire x1="3.048" y1="2.3368" x2="3.048" y2="3.048" width="0.2032" layer="21"/>
<wire x1="3.048" y1="3.048" x2="2.3368" y2="3.048" width="0.2032" layer="21"/>
<wire x1="-2.3368" y1="3.048" x2="-3.048" y2="3.048" width="0.2032" layer="21"/>
<wire x1="-3.048" y1="3.048" x2="-3.048" y2="2.3368" width="0.2032" layer="21"/>
<circle x="-1.75" y="-2" radius="0.25" width="0.03" layer="51"/>
<smd name="1" x="-1.75" y="-3.1" dx="0.2936" dy="1.6" layer="1"/>
<smd name="2" x="-1.25" y="-3.1" dx="0.2936" dy="1.6" layer="1"/>
<smd name="3" x="-0.75" y="-3.1" dx="0.2936" dy="1.6" layer="1"/>
<smd name="4" x="-0.25" y="-3.1" dx="0.2936" dy="1.6" layer="1"/>
<smd name="5" x="0.25" y="-3.1" dx="0.2936" dy="1.6" layer="1"/>
<smd name="6" x="0.75" y="-3.1" dx="0.2936" dy="1.6" layer="1"/>
<smd name="7" x="1.25" y="-3.1" dx="0.2936" dy="1.6" layer="1"/>
<smd name="8" x="1.75" y="-3.1" dx="0.2936" dy="1.6" layer="1"/>
<smd name="9" x="3.1" y="-1.75" dx="1.6" dy="0.2936" layer="1"/>
<smd name="10" x="3.1" y="-1.25" dx="1.6" dy="0.2936" layer="1"/>
<smd name="11" x="3.1" y="-0.75" dx="1.6" dy="0.2936" layer="1"/>
<smd name="12" x="3.1" y="-0.25" dx="1.6" dy="0.2936" layer="1"/>
<smd name="13" x="3.1" y="0.25" dx="1.6" dy="0.2936" layer="1"/>
<smd name="14" x="3.1" y="0.75" dx="1.6" dy="0.2936" layer="1"/>
<smd name="15" x="3.1" y="1.25" dx="1.6" dy="0.2936" layer="1"/>
<smd name="16" x="3.1" y="1.75" dx="1.6" dy="0.2936" layer="1"/>
<smd name="17" x="1.75" y="3.1" dx="0.2936" dy="1.6" layer="1"/>
<smd name="18" x="1.25" y="3.1" dx="0.2936" dy="1.6" layer="1"/>
<smd name="19" x="0.75" y="3.1" dx="0.2936" dy="1.6" layer="1"/>
<smd name="20" x="0.25" y="3.1" dx="0.2936" dy="1.6" layer="1"/>
<smd name="21" x="-0.25" y="3.1" dx="0.2936" dy="1.6" layer="1"/>
<smd name="22" x="-0.75" y="3.1" dx="0.2936" dy="1.6" layer="1"/>
<smd name="23" x="-1.25" y="3.1" dx="0.2936" dy="1.6" layer="1"/>
<smd name="24" x="-1.75" y="3.1" dx="0.2936" dy="1.6" layer="1"/>
<smd name="25" x="-3.1" y="1.75" dx="1.6" dy="0.2936" layer="1"/>
<smd name="26" x="-3.1" y="1.25" dx="1.6" dy="0.2936" layer="1"/>
<smd name="27" x="-3.1" y="0.75" dx="1.6" dy="0.2936" layer="1"/>
<smd name="28" x="-3.1" y="0.25" dx="1.6" dy="0.2936" layer="1"/>
<smd name="29" x="-3.1" y="-0.25" dx="1.6" dy="0.2936" layer="1"/>
<smd name="30" x="-3.1" y="-0.75" dx="1.6" dy="0.2936" layer="1"/>
<smd name="31" x="-3.1" y="-1.25" dx="1.6" dy="0.2936" layer="1"/>
<smd name="32" x="-3.1" y="-1.75" dx="1.6" dy="0.2936" layer="1"/>
<text x="-4.445" y="-3.81" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="5.715" y="-3.81" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="MAX3421E">
<wire x1="-17.78" y1="25.4" x2="-17.78" y2="-27.94" width="0.254" layer="94"/>
<wire x1="-17.78" y1="-27.94" x2="17.78" y2="-27.94" width="0.254" layer="94"/>
<wire x1="17.78" y1="-27.94" x2="17.78" y2="25.4" width="0.254" layer="94"/>
<wire x1="17.78" y1="25.4" x2="-17.78" y2="25.4" width="0.254" layer="94"/>
<text x="-17.78" y="-33.02" size="1.778" layer="95">&gt;NAME</text>
<text x="-17.78" y="-35.56" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GPIN7" x="22.86" y="-2.54" length="middle" direction="in" rot="R180"/>
<pin name="VL" x="-5.08" y="30.48" length="middle" direction="in" rot="R270"/>
<pin name="GND@1" x="-2.54" y="-33.02" length="middle" direction="sup" rot="R90"/>
<pin name="GPOUT0" x="22.86" y="-7.62" length="middle" direction="out" rot="R180"/>
<pin name="GPOUT1" x="22.86" y="-10.16" length="middle" direction="out" rot="R180"/>
<pin name="GPOUT2" x="22.86" y="-12.7" length="middle" direction="out" rot="R180"/>
<pin name="GPOUT3" x="22.86" y="-15.24" length="middle" direction="out" rot="R180"/>
<pin name="GPOUT4" x="22.86" y="-17.78" length="middle" direction="out" rot="R180"/>
<pin name="XO" x="-22.86" y="-10.16" length="middle" direction="out"/>
<pin name="GPIN0" x="22.86" y="15.24" length="middle" direction="in" rot="R180"/>
<pin name="GPIN1" x="22.86" y="12.7" length="middle" direction="in" rot="R180"/>
<pin name="GPIN2" x="22.86" y="10.16" length="middle" direction="in" rot="R180"/>
<pin name="GPIN3" x="22.86" y="7.62" length="middle" direction="in" rot="R180"/>
<pin name="GPIN4" x="22.86" y="5.08" length="middle" direction="in" rot="R180"/>
<pin name="GPIN5" x="22.86" y="2.54" length="middle" direction="in" rot="R180"/>
<pin name="GPIN6" x="22.86" y="0" length="middle" direction="in" rot="R180"/>
<pin name="XI" x="-22.86" y="-25.4" length="middle" direction="in"/>
<pin name="VCC" x="-12.7" y="30.48" length="middle" direction="sup" rot="R270"/>
<pin name="VBCOMP" x="-22.86" y="-2.54" length="middle" direction="in"/>
<pin name="D+" x="-22.86" y="15.24" length="middle"/>
<pin name="D-" x="-22.86" y="5.08" length="middle"/>
<pin name="GND@2" x="2.54" y="-33.02" length="middle" direction="sup" rot="R90"/>
<pin name="INT" x="2.54" y="30.48" length="middle" direction="out" rot="R270"/>
<pin name="GPX" x="5.08" y="30.48" length="middle" direction="out" rot="R270"/>
<pin name="MOSI" x="7.62" y="30.48" length="middle" direction="in" rot="R270"/>
<pin name="MISO" x="10.16" y="30.48" length="middle" direction="out" rot="R270"/>
<pin name="SS" x="15.24" y="30.48" length="middle" direction="in" rot="R270"/>
<pin name="SCLK" x="12.7" y="30.48" length="middle" direction="in" rot="R270"/>
<pin name="RES" x="0" y="30.48" length="middle" direction="in" rot="R270"/>
<pin name="GPOUT7" x="22.86" y="-25.4" length="middle" direction="out" rot="R180"/>
<pin name="GPOUT6" x="22.86" y="-22.86" length="middle" direction="out" rot="R180"/>
<pin name="GPOUT5" x="22.86" y="-20.32" length="middle" direction="out" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MAX3421E">
<gates>
<gate name="G$1" symbol="MAX3421E" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TQFP32_8MIL">
<connects>
<connect gate="G$1" pin="D+" pad="21"/>
<connect gate="G$1" pin="D-" pad="20"/>
<connect gate="G$1" pin="GND@1" pad="3"/>
<connect gate="G$1" pin="GND@2" pad="19"/>
<connect gate="G$1" pin="GPIN0" pad="26"/>
<connect gate="G$1" pin="GPIN1" pad="27"/>
<connect gate="G$1" pin="GPIN2" pad="28"/>
<connect gate="G$1" pin="GPIN3" pad="29"/>
<connect gate="G$1" pin="GPIN4" pad="30"/>
<connect gate="G$1" pin="GPIN5" pad="31"/>
<connect gate="G$1" pin="GPIN6" pad="32"/>
<connect gate="G$1" pin="GPIN7" pad="1"/>
<connect gate="G$1" pin="GPOUT0" pad="4"/>
<connect gate="G$1" pin="GPOUT1" pad="5"/>
<connect gate="G$1" pin="GPOUT2" pad="6"/>
<connect gate="G$1" pin="GPOUT3" pad="7"/>
<connect gate="G$1" pin="GPOUT4" pad="8"/>
<connect gate="G$1" pin="GPOUT5" pad="9"/>
<connect gate="G$1" pin="GPOUT6" pad="10"/>
<connect gate="G$1" pin="GPOUT7" pad="11"/>
<connect gate="G$1" pin="GPX" pad="17"/>
<connect gate="G$1" pin="INT" pad="18"/>
<connect gate="G$1" pin="MISO" pad="15"/>
<connect gate="G$1" pin="MOSI" pad="16"/>
<connect gate="G$1" pin="RES" pad="12"/>
<connect gate="G$1" pin="SCLK" pad="13"/>
<connect gate="G$1" pin="SS" pad="14"/>
<connect gate="G$1" pin="VBCOMP" pad="22"/>
<connect gate="G$1" pin="VCC" pad="23"/>
<connect gate="G$1" pin="VL" pad="2"/>
<connect gate="G$1" pin="XI" pad="24"/>
<connect gate="G$1" pin="XO" pad="25"/>
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
<class number="3" name="3.3V" width="0" drill="0">
</class>
<class number="4" name="I/O" width="0" drill="0">
</class>
</classes>
<parts>
<part name="GND5" library="supply1" deviceset="GND" device=""/>
<part name="GND21" library="supply1" deviceset="GND" device=""/>
<part name="JP1" library="My Parts" deviceset="8-PIN_HEADER" device=""/>
<part name="JP2" library="My Parts" deviceset="8-PIN_HEADER" device=""/>
<part name="JP3" library="My Parts" deviceset="8-PIN_HEADER" device=""/>
<part name="JP4" library="My Parts" deviceset="8-PIN_HEADER" device=""/>
<part name="+3V1" library="supply1" deviceset="+3V3" device=""/>
<part name="P+1" library="supply1" deviceset="+5V" device=""/>
<part name="P+2" library="supply1" deviceset="VCC" device=""/>
<part name="U1" library="CH_Maxim" deviceset="MAX3421E" device=""/>
<part name="R1" library="CH_passive" deviceset="RESISTOR" device="0603" value="33 1%"/>
<part name="R2" library="CH_passive" deviceset="RESISTOR" device="0603" value="33 1%"/>
<part name="GND4" library="CH_passive" deviceset="GND" device=""/>
<part name="C3" library="CH_passive" deviceset="CAP" device="0603" value="0.1uF"/>
<part name="C4" library="CH_passive" deviceset="CAP_POL" device="1206" value="4.7uF"/>
<part name="GND10" library="CH_passive" deviceset="GND" device=""/>
<part name="C8" library="CH_passive" deviceset="CAP" device="0603" value="18pF"/>
<part name="C9" library="CH_passive" deviceset="CAP" device="0603" value="18pF"/>
<part name="GND12" library="CH_passive" deviceset="GND" device=""/>
<part name="R4" library="CH_passive" deviceset="RESISTOR" device="0603" value="2.2K"/>
<part name="Q1" library="CH_passive" deviceset="CRYSTAL_SH" device="" value="12MHz"/>
<part name="P+3" library="supply1" deviceset="+5V" device=""/>
<part name="+3V2" library="supply1" deviceset="+3V3" device=""/>
<part name="U$1" library="My Parts" deviceset="USB_SOCKET" device="TYPE-A">
<attribute name="PART#" value="USB-A1HSW6"/>
</part>
<part name="GND1" library="CH_passive" deviceset="GND" device=""/>
</parts>
<sheets>
<sheet>
<plain>
<text x="-3.81" y="0" size="2.54" layer="91" ratio="15">~</text>
<text x="-3.81" y="2.54" size="2.54" layer="91" ratio="15">~</text>
<text x="-3.81" y="33.02" size="2.54" layer="91" ratio="15">~</text>
<text x="-3.81" y="30.48" size="2.54" layer="91" ratio="15">~</text>
<text x="-3.81" y="60.96" size="2.54" layer="91" ratio="15">~</text>
<text x="-3.81" y="63.5" size="2.54" layer="91" ratio="15">~</text>
<text x="-3.81" y="35.56" size="2.54" layer="91" ratio="15">~</text>
<text x="-3.81" y="83.82" size="2.54" layer="91" ratio="15">~</text>
<text x="3.81" y="120.65" size="2.54" layer="91" ratio="15">= 3.3v only!</text>
<text x="0.635" y="119.38" size="2.54" layer="91" ratio="15">~</text>
<text x="-3.175" y="87.63" size="1.778" layer="91" ratio="15">*</text>
<text x="-3.175" y="92.71" size="1.778" layer="91" ratio="15">*</text>
<text x="-3.175" y="95.25" size="1.778" layer="91" ratio="15">*</text>
<text x="-3.175" y="41.91" size="1.778" layer="91" ratio="15">*</text>
<text x="-3.175" y="13.97" size="1.778" layer="91" ratio="15">*</text>
<text x="-3.175" y="11.43" size="1.778" layer="91" ratio="15">*</text>
<text x="0.635" y="117.475" size="1.778" layer="91" ratio="15">*</text>
<text x="3.81" y="116.84" size="2.54" layer="91" ratio="15">= 5/3.3v (depends on solder jumpers</text>
<text x="0.635" y="113.665" size="2.54" layer="91" ratio="15">Recommend only using 3.3v, even though some pins are 5v tolerant</text>
<text x="-3.175" y="98.044" size="1.778" layer="91" ratio="15">*</text>
<text x="-3.175" y="100.584" size="1.778" layer="91" ratio="15">*</text>
</plain>
<instances>
<instance part="GND5" gate="1" x="17.78" y="25.4"/>
<instance part="GND21" gate="1" x="12.7" y="53.34"/>
<instance part="JP1" gate="G$1" x="5.08" y="96.52" smashed="yes" rot="MR0">
<attribute name="NAME" x="8.89" y="107.315" size="1.778" layer="95" rot="MR0"/>
</instance>
<instance part="JP2" gate="G$1" x="5.08" y="68.58" smashed="yes" rot="MR0">
<attribute name="NAME" x="8.89" y="79.375" size="1.778" layer="95" rot="MR0"/>
</instance>
<instance part="JP3" gate="G$1" x="5.08" y="40.64" smashed="yes" rot="MR0">
<attribute name="NAME" x="8.89" y="51.435" size="1.778" layer="95" rot="MR0"/>
</instance>
<instance part="JP4" gate="G$1" x="5.08" y="12.7" smashed="yes" rot="MR0">
<attribute name="NAME" x="8.89" y="23.495" size="1.778" layer="95" rot="MR0"/>
</instance>
<instance part="+3V1" gate="G$1" x="15.24" y="111.76"/>
<instance part="P+1" gate="1" x="25.4" y="27.94"/>
<instance part="P+2" gate="VCC" x="30.48" y="66.04"/>
<instance part="U1" gate="G$1" x="124.46" y="43.18"/>
<instance part="R1" gate="G$1" x="96.52" y="58.42" smashed="yes">
<attribute name="NAME" x="92.71" y="59.9186" size="1.778" layer="95"/>
<attribute name="VALUE" x="92.71" y="55.118" size="1.778" layer="96"/>
</instance>
<instance part="R2" gate="G$1" x="96.52" y="48.26" smashed="yes">
<attribute name="NAME" x="92.71" y="49.7586" size="1.778" layer="95"/>
<attribute name="VALUE" x="92.71" y="44.958" size="1.778" layer="96"/>
</instance>
<instance part="GND4" gate="1" x="68.58" y="40.64"/>
<instance part="C3" gate="G$1" x="76.2" y="50.8" smashed="yes">
<attribute name="NAME" x="73.66" y="40.64" size="1.778" layer="95"/>
<attribute name="VALUE" x="73.66" y="38.1" size="1.778" layer="96"/>
</instance>
<instance part="C4" gate="G$1" x="83.82" y="53.34" smashed="yes">
<attribute name="NAME" x="81.28" y="40.64" size="1.778" layer="95"/>
<attribute name="VALUE" x="81.28" y="38.1" size="1.778" layer="96"/>
</instance>
<instance part="GND10" gate="1" x="124.46" y="7.62"/>
<instance part="C8" gate="G$1" x="83.82" y="33.02" smashed="yes" rot="R90">
<attribute name="NAME" x="83.82" y="35.56" size="1.778" layer="95"/>
<attribute name="VALUE" x="88.9" y="35.56" size="1.778" layer="96"/>
</instance>
<instance part="C9" gate="G$1" x="83.82" y="17.78" smashed="yes" rot="R90">
<attribute name="NAME" x="81.28" y="22.86" size="1.778" layer="95"/>
<attribute name="VALUE" x="81.28" y="20.32" size="1.778" layer="96"/>
</instance>
<instance part="GND12" gate="1" x="88.9" y="10.16"/>
<instance part="R4" gate="G$1" x="127" y="88.9" smashed="yes" rot="R90">
<attribute name="NAME" x="129.54" y="88.9" size="1.778" layer="95"/>
<attribute name="VALUE" x="129.54" y="86.36" size="1.778" layer="96"/>
</instance>
<instance part="Q1" gate="G$1" x="93.98" y="25.4" smashed="yes" rot="R90">
<attribute name="NAME" x="96.52" y="30.48" size="1.778" layer="95"/>
<attribute name="VALUE" x="96.52" y="27.94" size="1.778" layer="96"/>
</instance>
<instance part="P+3" gate="1" x="83.82" y="71.12"/>
<instance part="+3V2" gate="G$1" x="127" y="99.06"/>
<instance part="U$1" gate="G$1" x="58.42" y="60.96" rot="R180">
<attribute name="PART#" x="58.42" y="60.96" size="1.778" layer="96" rot="R180" display="off"/>
</instance>
<instance part="GND1" gate="1" x="60.96" y="73.66" rot="R180"/>
</instances>
<busses>
</busses>
<nets>
<net name="GND" class="0">
<segment>
<pinref part="JP2" gate="G$1" pin="8"/>
<pinref part="GND21" gate="1" pin="GND"/>
<wire x1="5.08" y1="58.42" x2="12.7" y2="58.42" width="0.1524" layer="91"/>
<wire x1="12.7" y1="58.42" x2="12.7" y2="55.88" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="JP3" gate="G$1" pin="8"/>
<pinref part="GND5" gate="1" pin="GND"/>
<wire x1="5.08" y1="30.48" x2="12.7" y2="30.48" width="0.1524" layer="91"/>
<wire x1="12.7" y1="30.48" x2="17.78" y2="30.48" width="0.1524" layer="91"/>
<wire x1="17.78" y1="30.48" x2="17.78" y2="27.94" width="0.1524" layer="91"/>
<pinref part="JP4" gate="G$1" pin="2"/>
<wire x1="5.08" y1="17.78" x2="12.7" y2="17.78" width="0.1524" layer="91"/>
<wire x1="12.7" y1="17.78" x2="12.7" y2="30.48" width="0.1524" layer="91"/>
<junction x="12.7" y="30.48"/>
</segment>
<segment>
<wire x1="78.74" y1="33.02" x2="78.74" y2="17.78" width="0.1524" layer="91"/>
<wire x1="78.74" y1="17.78" x2="78.74" y2="12.7" width="0.1524" layer="91"/>
<wire x1="78.74" y1="12.7" x2="88.9" y2="12.7" width="0.1524" layer="91"/>
<wire x1="88.9" y1="25.4" x2="88.9" y2="12.7" width="0.1524" layer="91"/>
<wire x1="99.06" y1="25.4" x2="99.06" y2="12.7" width="0.1524" layer="91"/>
<wire x1="99.06" y1="12.7" x2="88.9" y2="12.7" width="0.1524" layer="91"/>
<junction x="78.74" y="17.78"/>
<junction x="88.9" y="12.7"/>
<junction x="88.9" y="12.7"/>
<pinref part="C8" gate="G$1" pin="1"/>
<pinref part="GND12" gate="1" pin="GND"/>
<pinref part="C9" gate="G$1" pin="1"/>
<pinref part="Q1" gate="G$1" pin="3"/>
<pinref part="Q1" gate="G$1" pin="4"/>
</segment>
<segment>
<wire x1="76.2" y1="48.26" x2="76.2" y2="43.18" width="0.1524" layer="91"/>
<wire x1="83.82" y1="48.26" x2="83.82" y2="43.18" width="0.1524" layer="91"/>
<wire x1="83.82" y1="43.18" x2="76.2" y2="43.18" width="0.1524" layer="91"/>
<wire x1="76.2" y1="43.18" x2="68.58" y2="43.18" width="0.1524" layer="91"/>
<junction x="76.2" y="43.18"/>
<pinref part="C3" gate="G$1" pin="2"/>
<pinref part="C4" gate="G$1" pin="-"/>
<pinref part="GND4" gate="1" pin="GND"/>
</segment>
<segment>
<wire x1="124.46" y1="10.16" x2="127" y2="10.16" width="0.1524" layer="91"/>
<wire x1="121.92" y1="10.16" x2="124.46" y2="10.16" width="0.1524" layer="91"/>
<junction x="124.46" y="10.16"/>
<pinref part="U1" gate="G$1" pin="GND@2"/>
<pinref part="GND10" gate="1" pin="GND"/>
<pinref part="U1" gate="G$1" pin="GND@1"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="GND"/>
<wire x1="63.5" y1="63.5" x2="63.5" y2="71.12" width="0.1524" layer="91"/>
<pinref part="GND1" gate="1" pin="GND"/>
<wire x1="63.5" y1="71.12" x2="60.96" y2="71.12" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="P$1"/>
<wire x1="58.42" y1="68.58" x2="58.42" y2="71.12" width="0.1524" layer="91"/>
<wire x1="58.42" y1="71.12" x2="60.96" y2="71.12" width="0.1524" layer="91"/>
<junction x="60.96" y="71.12"/>
<pinref part="U$1" gate="G$1" pin="P$2"/>
<wire x1="55.88" y1="68.58" x2="55.88" y2="71.12" width="0.1524" layer="91"/>
<wire x1="55.88" y1="71.12" x2="58.42" y2="71.12" width="0.1524" layer="91"/>
<junction x="58.42" y="71.12"/>
</segment>
</net>
<net name="MISO" class="0">
<segment>
<pinref part="JP2" gate="G$1" pin="6"/>
<wire x1="5.08" y1="63.5" x2="22.86" y2="63.5" width="0.1524" layer="91"/>
<label x="10.16" y="63.5" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="134.62" y1="83.82" x2="134.62" y2="73.66" width="0.1524" layer="91"/>
<label x="134.366" y="76.2" size="1.778" layer="95" rot="R90"/>
<pinref part="U1" gate="G$1" pin="MISO"/>
</segment>
</net>
<net name="MOSI" class="0">
<segment>
<pinref part="JP2" gate="G$1" pin="5"/>
<wire x1="5.08" y1="66.04" x2="22.86" y2="66.04" width="0.1524" layer="91"/>
<label x="10.16" y="66.04" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="132.08" y1="83.82" x2="132.08" y2="73.66" width="0.1524" layer="91"/>
<label x="131.826" y="76.2" size="1.778" layer="95" rot="R90"/>
<pinref part="U1" gate="G$1" pin="MOSI"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="JP2" gate="G$1" pin="4"/>
<wire x1="5.08" y1="68.58" x2="22.86" y2="68.58" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="JP2" gate="G$1" pin="3"/>
<wire x1="5.08" y1="71.12" x2="22.86" y2="71.12" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="JP2" gate="G$1" pin="2"/>
<wire x1="5.08" y1="73.66" x2="22.86" y2="73.66" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="JP2" gate="G$1" pin="1"/>
<wire x1="5.08" y1="76.2" x2="22.86" y2="76.2" width="0.1524" layer="91"/>
</segment>
</net>
<net name="MEMORY_CS" class="0">
<segment>
<pinref part="JP1" gate="G$1" pin="8"/>
<wire x1="5.08" y1="86.36" x2="25.4" y2="86.36" width="0.1524" layer="91"/>
<label x="10.16" y="86.36" size="1.778" layer="95"/>
</segment>
</net>
<net name="IMU_INT" class="0">
<segment>
<pinref part="JP1" gate="G$1" pin="7"/>
<wire x1="5.08" y1="88.9" x2="25.4" y2="88.9" width="0.1524" layer="91"/>
<label x="10.16" y="88.9" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="JP1" gate="G$1" pin="6"/>
<wire x1="5.08" y1="91.44" x2="25.4" y2="91.44" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SERVO_2" class="0">
<segment>
<pinref part="JP1" gate="G$1" pin="5"/>
<wire x1="5.08" y1="93.98" x2="25.4" y2="93.98" width="0.1524" layer="91"/>
<label x="10.16" y="93.98" size="1.778" layer="95"/>
</segment>
</net>
<net name="SERVO_1" class="0">
<segment>
<pinref part="JP1" gate="G$1" pin="4"/>
<wire x1="5.08" y1="96.52" x2="25.4" y2="96.52" width="0.1524" layer="91"/>
<label x="10.16" y="96.52" size="1.778" layer="95"/>
</segment>
</net>
<net name="BLUETOOTH_TX" class="0">
<segment>
<pinref part="JP1" gate="G$1" pin="3"/>
<wire x1="5.08" y1="99.06" x2="25.4" y2="99.06" width="0.1524" layer="91"/>
<label x="10.16" y="99.06" size="1.778" layer="95"/>
</segment>
</net>
<net name="BLUETOOTH_RX" class="0">
<segment>
<pinref part="JP1" gate="G$1" pin="2"/>
<wire x1="5.08" y1="101.6" x2="25.4" y2="101.6" width="0.1524" layer="91"/>
<label x="10.16" y="101.6" size="1.778" layer="95"/>
</segment>
</net>
<net name="5V_SDA" class="0">
<segment>
<pinref part="JP3" gate="G$1" pin="1"/>
<wire x1="5.08" y1="48.26" x2="22.86" y2="48.26" width="0.1524" layer="91"/>
<label x="10.16" y="48.26" size="1.778" layer="95"/>
</segment>
</net>
<net name="5V_SCL" class="0">
<segment>
<pinref part="JP3" gate="G$1" pin="2"/>
<wire x1="5.08" y1="45.72" x2="22.86" y2="45.72" width="0.1524" layer="91"/>
<label x="10.16" y="45.72" size="1.778" layer="95"/>
</segment>
</net>
<net name="BT_CMD" class="0">
<segment>
<pinref part="JP3" gate="G$1" pin="3"/>
<wire x1="5.08" y1="43.18" x2="22.86" y2="43.18" width="0.1524" layer="91"/>
<label x="10.16" y="43.18" size="1.778" layer="95"/>
</segment>
</net>
<net name="BATT_SENSE" class="0">
<segment>
<pinref part="JP3" gate="G$1" pin="4"/>
<wire x1="5.08" y1="40.64" x2="22.86" y2="40.64" width="0.1524" layer="91"/>
<label x="10.16" y="40.64" size="1.778" layer="95"/>
</segment>
</net>
<net name="SCK" class="0">
<segment>
<pinref part="JP3" gate="G$1" pin="5"/>
<wire x1="5.08" y1="38.1" x2="22.86" y2="38.1" width="0.1524" layer="91"/>
<label x="10.16" y="38.1" size="1.778" layer="95"/>
</segment>
</net>
<net name="AUX_SDA" class="0">
<segment>
<pinref part="JP3" gate="G$1" pin="6"/>
<wire x1="5.08" y1="35.56" x2="22.86" y2="35.56" width="0.1524" layer="91"/>
<label x="10.16" y="35.56" size="1.778" layer="95"/>
</segment>
</net>
<net name="AUX_SCL" class="0">
<segment>
<pinref part="JP3" gate="G$1" pin="7"/>
<wire x1="5.08" y1="33.02" x2="22.86" y2="33.02" width="0.1524" layer="91"/>
<label x="10.16" y="33.02" size="1.778" layer="95"/>
</segment>
</net>
<net name="SERVO_4" class="0">
<segment>
<pinref part="JP4" gate="G$1" pin="3"/>
<wire x1="5.08" y1="15.24" x2="22.86" y2="15.24" width="0.1524" layer="91"/>
<label x="12.7" y="15.24" size="1.778" layer="95"/>
</segment>
</net>
<net name="SERVO_3" class="0">
<segment>
<pinref part="JP4" gate="G$1" pin="4"/>
<wire x1="5.08" y1="12.7" x2="22.86" y2="12.7" width="0.1524" layer="91"/>
<label x="12.7" y="12.7" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$26" class="0">
<segment>
<pinref part="JP4" gate="G$1" pin="5"/>
<wire x1="5.08" y1="10.16" x2="22.86" y2="10.16" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$27" class="0">
<segment>
<pinref part="JP4" gate="G$1" pin="6"/>
<wire x1="5.08" y1="7.62" x2="22.86" y2="7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="3V_SCL" class="0">
<segment>
<pinref part="JP4" gate="G$1" pin="7"/>
<wire x1="5.08" y1="5.08" x2="22.86" y2="5.08" width="0.1524" layer="91"/>
<label x="10.16" y="5.08" size="1.778" layer="95"/>
</segment>
</net>
<net name="3V_SDA" class="0">
<segment>
<pinref part="JP4" gate="G$1" pin="8"/>
<wire x1="5.08" y1="2.54" x2="22.86" y2="2.54" width="0.1524" layer="91"/>
<label x="10.16" y="2.54" size="1.778" layer="95"/>
</segment>
</net>
<net name="+3V3" class="0">
<segment>
<pinref part="JP1" gate="G$1" pin="1"/>
<pinref part="+3V1" gate="G$1" pin="+3V3"/>
<wire x1="5.08" y1="104.14" x2="15.24" y2="104.14" width="0.1524" layer="91"/>
<wire x1="15.24" y1="104.14" x2="15.24" y2="109.22" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="111.76" y1="73.66" x2="119.38" y2="73.66" width="0.1524" layer="91"/>
<wire x1="119.38" y1="73.66" x2="119.38" y2="93.98" width="0.1524" layer="91"/>
<wire x1="119.38" y1="93.98" x2="127" y2="93.98" width="0.1524" layer="91"/>
<junction x="119.38" y="73.66"/>
<pinref part="U1" gate="G$1" pin="VL"/>
<pinref part="U1" gate="G$1" pin="VCC"/>
<pinref part="R4" gate="G$1" pin="2"/>
<pinref part="+3V2" gate="G$1" pin="+3V3"/>
<wire x1="127" y1="93.98" x2="127" y2="96.52" width="0.1524" layer="91"/>
<junction x="127" y="93.98"/>
</segment>
</net>
<net name="+5V" class="0">
<segment>
<pinref part="JP4" gate="G$1" pin="1"/>
<pinref part="P+1" gate="1" pin="+5V"/>
<wire x1="5.08" y1="20.32" x2="25.4" y2="20.32" width="0.1524" layer="91"/>
<wire x1="25.4" y1="20.32" x2="25.4" y2="25.4" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="83.82" y1="55.88" x2="83.82" y2="63.5" width="0.1524" layer="91"/>
<wire x1="83.82" y1="63.5" x2="76.2" y2="63.5" width="0.1524" layer="91"/>
<wire x1="76.2" y1="63.5" x2="76.2" y2="55.88" width="0.1524" layer="91"/>
<wire x1="76.2" y1="63.5" x2="66.04" y2="63.5" width="0.1524" layer="91"/>
<junction x="76.2" y="63.5"/>
<label x="68.58" y="63.754" size="1.778" layer="95"/>
<pinref part="C3" gate="G$1" pin="1"/>
<pinref part="C4" gate="G$1" pin="+"/>
<pinref part="P+3" gate="1" pin="+5V"/>
<wire x1="83.82" y1="63.5" x2="83.82" y2="68.58" width="0.1524" layer="91"/>
<junction x="83.82" y="63.5"/>
<wire x1="66.04" y1="63.5" x2="66.04" y2="60.96" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="VBUS"/>
<wire x1="66.04" y1="60.96" x2="63.5" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="VCC" class="0">
<segment>
<pinref part="JP2" gate="G$1" pin="7"/>
<wire x1="5.08" y1="60.96" x2="30.48" y2="60.96" width="0.1524" layer="91"/>
<pinref part="P+2" gate="VCC" pin="VCC"/>
<wire x1="30.48" y1="60.96" x2="30.48" y2="63.5" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="D+"/>
<pinref part="R1" gate="G$1" pin="2"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="D-"/>
<pinref part="R2" gate="G$1" pin="2"/>
</segment>
</net>
<net name="N$40" class="0">
<segment>
<wire x1="86.36" y1="33.02" x2="93.98" y2="33.02" width="0.1524" layer="91"/>
<wire x1="93.98" y1="33.02" x2="101.6" y2="33.02" width="0.1524" layer="91"/>
<wire x1="93.98" y1="27.94" x2="93.98" y2="33.02" width="0.1524" layer="91"/>
<junction x="93.98" y="33.02"/>
<pinref part="U1" gate="G$1" pin="XO"/>
<pinref part="C8" gate="G$1" pin="2"/>
<pinref part="Q1" gate="G$1" pin="2"/>
</segment>
</net>
<net name="N$41" class="0">
<segment>
<wire x1="86.36" y1="17.78" x2="93.98" y2="17.78" width="0.1524" layer="91"/>
<wire x1="93.98" y1="17.78" x2="101.6" y2="17.78" width="0.1524" layer="91"/>
<wire x1="93.98" y1="22.86" x2="93.98" y2="17.78" width="0.1524" layer="91"/>
<junction x="93.98" y="17.78"/>
<pinref part="U1" gate="G$1" pin="XI"/>
<pinref part="C9" gate="G$1" pin="2"/>
<pinref part="Q1" gate="G$1" pin="1"/>
</segment>
</net>
<net name="SS" class="0">
<segment>
<wire x1="139.7" y1="83.82" x2="139.7" y2="73.66" width="0.1524" layer="91"/>
<label x="139.446" y="76.2" size="1.778" layer="95" rot="R90"/>
<pinref part="U1" gate="G$1" pin="SS"/>
</segment>
</net>
<net name="SCLK" class="0">
<segment>
<wire x1="137.16" y1="83.82" x2="137.16" y2="73.66" width="0.1524" layer="91"/>
<label x="136.906" y="76.2" size="1.778" layer="95" rot="R90"/>
<pinref part="U1" gate="G$1" pin="SCLK"/>
</segment>
</net>
<net name="GPX" class="0">
<segment>
<wire x1="129.54" y1="83.82" x2="129.54" y2="73.66" width="0.1524" layer="91"/>
<label x="129.286" y="76.2" size="1.778" layer="95" rot="R90"/>
<pinref part="U1" gate="G$1" pin="GPX"/>
</segment>
</net>
<net name="INT" class="0">
<segment>
<wire x1="127" y1="83.82" x2="127" y2="73.66" width="0.1524" layer="91"/>
<label x="126.746" y="76.2" size="1.778" layer="95" rot="R90"/>
<pinref part="U1" gate="G$1" pin="INT"/>
<pinref part="R4" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$54" class="0">
<segment>
<wire x1="91.44" y1="48.26" x2="88.9" y2="48.26" width="0.1524" layer="91"/>
<pinref part="R2" gate="G$1" pin="1"/>
<wire x1="88.9" y1="48.26" x2="88.9" y2="60.96" width="0.1524" layer="91"/>
<wire x1="88.9" y1="60.96" x2="67.31" y2="60.96" width="0.1524" layer="91"/>
<wire x1="67.31" y1="60.96" x2="67.31" y2="58.42" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="D-"/>
<wire x1="67.31" y1="58.42" x2="63.5" y2="58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="MRST" class="0">
<segment>
<wire x1="124.46" y1="73.66" x2="124.46" y2="83.82" width="0.1524" layer="91"/>
<label x="124.206" y="76.2" size="1.778" layer="95" rot="R90"/>
<pinref part="U1" gate="G$1" pin="RES"/>
</segment>
</net>
<net name="GO0" class="0">
<segment>
<wire x1="154.94" y1="35.56" x2="147.32" y2="35.56" width="0.1524" layer="91"/>
<label x="149.86" y="35.56" size="1.778" layer="95"/>
<pinref part="U1" gate="G$1" pin="GPOUT0"/>
</segment>
</net>
<net name="GO1" class="0">
<segment>
<wire x1="154.94" y1="33.02" x2="147.32" y2="33.02" width="0.1524" layer="91"/>
<label x="149.86" y="33.02" size="1.778" layer="95"/>
<pinref part="U1" gate="G$1" pin="GPOUT1"/>
</segment>
</net>
<net name="GO2" class="0">
<segment>
<wire x1="154.94" y1="30.48" x2="147.32" y2="30.48" width="0.1524" layer="91"/>
<label x="149.86" y="30.48" size="1.778" layer="95"/>
<pinref part="U1" gate="G$1" pin="GPOUT2"/>
</segment>
</net>
<net name="GO3" class="0">
<segment>
<wire x1="154.94" y1="27.94" x2="147.32" y2="27.94" width="0.1524" layer="91"/>
<label x="149.86" y="27.94" size="1.778" layer="95"/>
<pinref part="U1" gate="G$1" pin="GPOUT3"/>
</segment>
</net>
<net name="GO4" class="0">
<segment>
<wire x1="154.94" y1="25.4" x2="147.32" y2="25.4" width="0.1524" layer="91"/>
<label x="149.86" y="25.4" size="1.778" layer="95"/>
<pinref part="U1" gate="G$1" pin="GPOUT4"/>
</segment>
</net>
<net name="GO5" class="0">
<segment>
<wire x1="154.94" y1="22.86" x2="147.32" y2="22.86" width="0.1524" layer="91"/>
<label x="149.86" y="22.86" size="1.778" layer="95"/>
<pinref part="U1" gate="G$1" pin="GPOUT5"/>
</segment>
</net>
<net name="GO7" class="0">
<segment>
<wire x1="154.94" y1="17.78" x2="147.32" y2="17.78" width="0.1524" layer="91"/>
<label x="149.86" y="17.78" size="1.778" layer="95"/>
<pinref part="U1" gate="G$1" pin="GPOUT7"/>
</segment>
</net>
<net name="GO6" class="0">
<segment>
<wire x1="154.94" y1="20.32" x2="147.32" y2="20.32" width="0.1524" layer="91"/>
<label x="149.86" y="20.32" size="1.778" layer="95"/>
<pinref part="U1" gate="G$1" pin="GPOUT6"/>
</segment>
</net>
<net name="GI7" class="0">
<segment>
<wire x1="162.56" y1="40.64" x2="147.32" y2="40.64" width="0.1524" layer="91"/>
<label x="149.86" y="40.64" size="1.778" layer="95"/>
<pinref part="U1" gate="G$1" pin="GPIN7"/>
</segment>
</net>
<net name="GI6" class="0">
<segment>
<wire x1="162.56" y1="43.18" x2="147.32" y2="43.18" width="0.1524" layer="91"/>
<label x="149.86" y="43.18" size="1.778" layer="95"/>
<pinref part="U1" gate="G$1" pin="GPIN6"/>
</segment>
</net>
<net name="GI5" class="0">
<segment>
<wire x1="162.56" y1="45.72" x2="147.32" y2="45.72" width="0.1524" layer="91"/>
<label x="149.86" y="45.72" size="1.778" layer="95"/>
<pinref part="U1" gate="G$1" pin="GPIN5"/>
</segment>
</net>
<net name="GI4" class="0">
<segment>
<wire x1="162.56" y1="48.26" x2="147.32" y2="48.26" width="0.1524" layer="91"/>
<label x="149.86" y="48.26" size="1.778" layer="95"/>
<pinref part="U1" gate="G$1" pin="GPIN4"/>
</segment>
</net>
<net name="GI3" class="0">
<segment>
<wire x1="162.56" y1="50.8" x2="147.32" y2="50.8" width="0.1524" layer="91"/>
<label x="149.86" y="50.8" size="1.778" layer="95"/>
<pinref part="U1" gate="G$1" pin="GPIN3"/>
</segment>
</net>
<net name="GI2" class="0">
<segment>
<wire x1="162.56" y1="53.34" x2="147.32" y2="53.34" width="0.1524" layer="91"/>
<label x="149.86" y="53.34" size="1.778" layer="95"/>
<pinref part="U1" gate="G$1" pin="GPIN2"/>
</segment>
</net>
<net name="GI1" class="0">
<segment>
<wire x1="162.56" y1="55.88" x2="147.32" y2="55.88" width="0.1524" layer="91"/>
<label x="149.86" y="55.88" size="1.778" layer="95"/>
<pinref part="U1" gate="G$1" pin="GPIN1"/>
</segment>
</net>
<net name="GI0" class="0">
<segment>
<wire x1="162.56" y1="58.42" x2="147.32" y2="58.42" width="0.1524" layer="91"/>
<label x="149.86" y="58.42" size="1.778" layer="95"/>
<pinref part="U1" gate="G$1" pin="GPIN0"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="D+"/>
<wire x1="63.5" y1="55.88" x2="68.58" y2="55.88" width="0.1524" layer="91"/>
<wire x1="68.58" y1="55.88" x2="68.58" y2="58.42" width="0.1524" layer="91"/>
<pinref part="R1" gate="G$1" pin="1"/>
<wire x1="68.58" y1="58.42" x2="91.44" y2="58.42" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
<errors>
<approved hash="104,1,203.2,60.96,U1,VIN,5V,,,"/>
<approved hash="204,1,203.2,53.34,U1,AGND,,,,"/>
<approved hash="104,1,203.2,58.42,U1,3.3V,TEENSY_3V3,,,"/>
<approved hash="106,1,106.68,25.4,CHASSIS_GND,,,,,"/>
<approved hash="115,1,142.003,50.6688,JP1,,,,,"/>
<approved hash="115,1,149.623,30.3488,JP2,,,,,"/>
<approved hash="115,1,241.537,50.6688,JP5,,,,,"/>
<approved hash="115,1,233.917,27.8088,JP6,,,,,"/>
<approved hash="115,1,234.908,110.621,JP3,,,,,"/>
<approved hash="115,1,234.908,85.2212,JP7,,,,,"/>
<approved hash="115,1,127.237,10.2912,JP8,,,,,"/>
<approved hash="115,1,254,95.8431,SJ3,,,,,"/>
<approved hash="115,1,254,121.243,SJ2,,,,,"/>
<approved hash="115,1,71.1369,67.4328,JP9,,,,,"/>
</errors>
</schematic>
</drawing>
</eagle>
