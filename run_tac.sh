#!/bin/bash
gcc -o tac_test tac.c tac_test_driver.c ../ast/ast.c -I../ast -Wall
./tac_test
