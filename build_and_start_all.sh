#!/usr/bin/env sh

######################################################################
# @author      : kistenklaus (karlsasssie@gmail.com)
# @file        : start_all
# @created     : Samstag Feb 17, 2024 00:15:42 CET
#
# @description : 
######################################################################

cmake -Binput_board/build -Sinput_board
make -C input_board/build
alacritty -e input_board/build/mock-input_board &

cmake -Bmaster/build -Smaster
make -C master/build
alacritty -e master/build/mock-master &

cmake -Bmgu1/build -Smgu1
make -C mgu1/build
alacritty -e mgu1/build/mock-mgu1 &

cmake -Bmgu2/build -Smgu2
make -C mgu2/build
alacritty -e mgu2/build/mock-mgu2 &

cmake -Bmlu1/build -Smlu1
make -C mlu1/build
alacritty -e mlu1/build/mock-mlu1 &

cmake -Bmlu2/build -Smlu2
make -C mlu2/build
alacritty -e mlu2/build/mock-mlu2 &

cmake -Bmlu3/build -Smlu3
make -C mlu3/build
alacritty -e mlu3/build/mock-mlu3 &

cmake -Bmlu4/build -Smlu4
make -C mlu4/build
alacritty -e mlu4/build/mock-mlu4 &

cmake -Bmlu5/build -Smlu5
make -C mlu5/build
alacritty -e mlu5/build/mock-mlu5 &

cmake -Bmlu6/build -Smlu6
make -C mlu6/build
alacritty -e mlu6/build/mock-mlu6 &

cmake -Bmotor_driver/build/ -Smotor_driver
make -C motor_driver/build
alacritty -e motor_driver/build/mock-motor_driver &

cmake -Bpdu12/build -Spdu12
make -C pdu12/build
alacritty -e pdu12/build/mock-pdu12 &

cmake -Bpdu24/build -Spdu24
make -C pdu24/build
alacritty -e pdu24/build/mock-pdu24 &

