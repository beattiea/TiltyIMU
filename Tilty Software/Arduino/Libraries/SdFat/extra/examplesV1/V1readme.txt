These are examples from SdFat V1.


These examples have been simplified by using new features of SdFat.


SdFatAppend.pde - This sketch creates a large file by successive
                  open/write/close operations using O_APPEND.

SdFatCopy.pde - Copy the file created by SdFatAppend.pde to the file
                ACOPY.TXT.

SdFatLs.pde - A test of the ls() file list function.

SdFatMakeDir.pde - A debug sketch to verify subdirectory creation and
                   access.

SdFatPrint.pde - This sketch shows how to use the Arduino Print class
                 with SdFat.

SdFatRead.pde  - This sketch reads and prints the file PRINT00.TXT
                 created by SdFatPrint.pde or WRITE00.TXT created by
                 SdFatWrite.pde.

SdFatRemove.pde - This sketch shows how to use remove() to delete the
                  file created by the SdFatAppend.pde example.

SdFatRewrite.pde - This sketch shows how to rewrite part of a line in
                   the middle of the file created by the
                   SdFatAppend.pde example.

SdFatRmDir.pde - A sketch to test file and directory deletion.


SdFatTail.pde  - This sketch reads and prints the tail of all files
                 created by SdFatAppend.pde, SdFatPrint.pde, and
                 SdFatWrite.pde.

SdFatTruncate.pde - This sketch shows how to use truncate() to remove
                    the last half of the file created by the
                    SdFatAppend.pde example.

SdFatWrite.pde - This sketch creates a new file and writes 100 lines
                 to the file.
