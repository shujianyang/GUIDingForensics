# GUIDingForensics


##Introduction
GUIDingForensics is a program which reads and analyzes globally unique identifiers (GUID) from GPT partitioned disk images.

In GPT partition system. Every disk and partition has one unique number, which is GUID.
For a GPT partition, in addition to a unique GUID, a partition type GUID is also given to mark the type of the partition.
All these GUIDs are stored in GUID partition table, which is why it is called GPT.

This program can read GUIDs from GPT system. Exctracted GUIDs can be further analyzed to obtain additional information.

##Platform:
Linux

##Prerequisite:
GUIDingForensics uses the Sleuth Kit (TSK) library to read data from forensic images.

You can find TSK in [sleuthkit/sleuthkit](https://github.com/sleuthkit/sleuthkit.git).

To install TSK library, please refer to INSTALL.txt in TSK repository.

##Usage:
`./guiding [-o offset] files`

-o: The offset to the start of the image in sectors.

##Input File:
Files with formats supported by TSK.

##Note:
GUIDingForensics can find a partition's type by reading its partition type GUID.
The standard partition type GUID list used in the program can be found here:

[https://en.wikipedia.org/wiki/GUID_Partition_Table#Partition_type_GUIDs](https://en.wikipedia.org/wiki/GUID_Partition_Table#Partition_type_GUIDs)

##License:
This software uses MIT License.

[The Sleuth Kit](https://github.com/sleuthkit/sleuthkit.git) library is used.


