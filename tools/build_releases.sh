#!/bin/bash

ORIGINAL_PWD=$(pwd)

# Create generic variant
TEMP=$(mktemp)
rm $TEMP
mkdir $TEMP
cp src/MAX40080.h $TEMP/MAX40080.h
cp src/MAX40080.c $TEMP/MAX40080.c
cp src/MAX40080_PlatformSpecific.h $TEMP/MAX40080_PlatformSpecific.h
cp src/MAX40080_PlatformSpecific.c $TEMP/MAX40080_PlatformSpecific.c
cd $TEMP
zip MAX40080_Generic.zip *
cd $ORIGINAL_PWD
cp $TEMP/MAX40080_Generic.zip releases/
rm -r $TEMP

# Create MAX32625 variant
TEMP=$(mktemp)
rm $TEMP
mkdir $TEMP
cp src/MAX40080.h $TEMP/MAX40080.h
cp src/MAX40080.c $TEMP/MAX40080.c
cp src/MAX40080_PlatformSpecific_MAX32625.h $TEMP/MAX40080_PlatformSpecific.h
cp src/MAX40080_PlatformSpecific_MAX32625.c $TEMP/MAX40080_PlatformSpecific.c
cd $TEMP
zip MAX40080_MAX32625.zip *
cd $ORIGINAL_PWD
cp $TEMP/MAX40080_MAX32625.zip releases/
rm -r $TEMP

# Create Linux variant
TEMP=$(mktemp)
rm $TEMP
mkdir $TEMP
cp src/MAX40080.h $TEMP/MAX40080.h
cp src/MAX40080.c $TEMP/MAX40080.c
cp src/MAX40080_PlatformSpecific_Linux.h $TEMP/MAX40080_PlatformSpecific.h
cp src/MAX40080_PlatformSpecific_Linux.c $TEMP/MAX40080_PlatformSpecific.c
cd $TEMP
zip MAX40080_Linux.zip *
cd $ORIGINAL_PWD
cp $TEMP/MAX40080_Linux.zip releases/
rm -r $TEMP


