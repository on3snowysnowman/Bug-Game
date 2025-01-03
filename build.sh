#!/bin/bash

cmake -G "Ninja" -B build -S .

cmake --build build
