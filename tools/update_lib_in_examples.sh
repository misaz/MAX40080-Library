#!/bin/bash

for i in examples/*/max32625; do
	echo "Patching \"$i\" example"
	cp src/MAX40080.h $i/MAX40080.h
	cp src/MAX40080.c $i/MAX40080.c
	cp src/MAX40080_PlatformSpecific_MAX32625.c $i/MAX40080_PlatformSpecific.c
	cp src/MAX40080_PlatformSpecific_MAX32625.h $i/MAX40080_PlatformSpecific.h
done

for i in examples/*/ra6m4; do
	echo "Patching \"$i\" example"
	cp src/MAX40080.h $i/src/MAX40080.h
	cp src/MAX40080.c $i/src/MAX40080.c
	cp src/MAX40080_PlatformSpecific_RA6M4.c $i/src/MAX40080_PlatformSpecific.c
	cp src/MAX40080_PlatformSpecific_RA6M4.h $i/src/MAX40080_PlatformSpecific.h
done
