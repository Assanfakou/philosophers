#!/bin/bash

gcc -g -fsanitize=thread *.c -o  philo
