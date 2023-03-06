#!/bin/sh

BUILD_DB=./RANMOJI.app/Contents/MacOS/ranmoji.db

if [ ! -f "$BUILD_DB" ]; then
	sqlite3 ./RANMOJI.app/Contents/MacOS/ranmoji.db < ./ranmoji.sqlite
fi
