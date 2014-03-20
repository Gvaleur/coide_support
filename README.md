coide_support
=============

Support for additional MCU's in COIDE

## Install

1. Merge the folders “flash” and “config” with the folders in the COIDE root folder.

2. Open COIDE.

3. Start a new project when prompted to select chip select ARM as manufacture and the appropriate aricture as device e.g. "M4".

4. In your new project open the Configuration window under the tab Link and file in the area "Memory Area" the appropriate values can be found in your device file e.g. "TM4C123H6PM.xml" under "...\coide\config\devices\"manufacture"".

5. Under the tab Download remove the path to the default programming algorithm and add the path to the one fitting your chip from "...\coide\flash" e.g. "TM4C123_256.elf" with the last number being the flash size of the chip.

6. Copy your device file e.g. "TM4C123H6PM.xml" from "...\coide\config\devices\"manufacture"" to "...\coide\config\devices\ARM" and rename it to your target device file e.g. "M4.xml" and overwrite the original.

Step 6 will have to be redone every time COIDE opens as it will regenerate the standard target files

## Support

### TI TIVA TM4C123

Erase = working

Programming = working

Debugging = working

libraries = added
