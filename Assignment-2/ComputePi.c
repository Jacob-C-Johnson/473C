/*
 * ComputePi.c - Main file for assignment 2 to compute pi
 *
 * Author: Jacob Johnson
 * Date: 02/03/2025
 *
 * Assignment: Assignment 2
 * Course: CSCI 473
 * Version 1.0
 */
#include<stdio.h>
#include<stdlib.h>
#include "utilities.h"


int main(int argc, char *argv[]) {
    // take n from command line input
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    double pi = compute_pi(n);
    printf("Estimate of pi is %f\n", pi);
    return 0;
}