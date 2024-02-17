#!/usr/bin/env sh

######################################################################
# @author      : kistenklaus (karlsasssie@gmail.com)
# @file        : start_all
# @created     : Samstag Feb 17, 2024 00:15:42 CET
#
# @description : 
######################################################################

cmake -Bbuild input_board/build
make -C input_board/build
alacritty -e input_board/build/mock-input_board &

cmake -Bbuild master/build
make -C master/build
alacritty -e master/build/mock-master &

cmake -Bbuild mgu1/build
make -C mgu1/build
alacritty -e mgu1/build/mock-mgu1 &

cmake -Bbuild mgu2/build
make -C mgu2/build
alacritty -e mgu2/build/mock-mgu2 &

cmake -Bbuild mlu1/build
make -C mlu1/build
alacritty -e mlu1/build/mock-mlu1 &

cmake -Bbuild mlu2/build
make -C mlu2/build
alacritty -e mlu2/build/mock-mlu2 &

cmake -Bbuild mlu3/build
make -C mlu3/build
alacritty -e mlu3/build/mock-mlu3 &

cmake -Bbuild mlu4/build
make -C mlu4/build
alacritty -e mlu4/build/mock-mlu4 &

cmake -Bbuild mlu5/build
make -C mlu5/build
alacritty -e mlu5/build/mock-mlu5 &

cmake -Bbuild mlu6/build
make -C mlu6/build
alacritty -e mlu6/build/mock-mlu6 &

cmake -Bbuild motor_driver/build/
make -C motor_driver/build
alacritty -e motor_driver/build/mock-motor_driver &

cmake -Bbuild pdu12/build
make -C pdu12/build
alacritty -e pdu12/build/mock-pdu12 &

cmake -Bbuild pdu24/build
make -C pdu24/build
alacritty -e pdu24/build/mock-pdu24 &
