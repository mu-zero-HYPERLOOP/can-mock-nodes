#!/usr/bin/env sh

######################################################################
# @author      : kistenklaus (karlsasssie@gmail.com)
# @file        : start_all
# @created     : Montag Feb 19, 2024 21:29:59 CET
#
# @description : 
######################################################################

alacritty -e input_board/build/mock-input_board &

alacritty -e master/build/mock-master &

alacritty -e mgu1/build/mock-mgu1 &

alacritty -e mgu2/build/mock-mgu2 &

alacritty -e mlu1/build/mock-mlu1 &

alacritty -e mlu2/build/mock-mlu2 &

alacritty -e mlu3/build/mock-mlu3 &

alacritty -e mlu4/build/mock-mlu4 &

alacritty -e mlu5/build/mock-mlu5 &

alacritty -e mlu6/build/mock-mlu6 &

alacritty -e motor_driver/build/mock-motor_driver &

alacritty -e pdu12/build/mock-pdu12 &

alacritty -e pdu24/build/mock-pdu24 &
