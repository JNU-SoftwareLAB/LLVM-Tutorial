#!/usr/bin/python3

# Setting
filename = "libLLVMPointerCheck.so"
option_name = "-pointer-check"

import os, argparse
import subprocess

parser = argparse.ArgumentParser()
parser.add_argument("testWay",help="0: compile & test Pass\n1: compile\n2:test Pass")

args = parser.parse_args()

# Configure Variable
dir_path = os.path.dirname(os.path.abspath(__file__))
test_target_path = os.path.join(dir_path, "HelloWorld.ll")
target_path = os.path.join(dir_path, "dest", filename)

# Compile
def compile():
	p1 = subprocess.Popen(["cmake", ".", "-B./dest"], stdout=subprocess.PIPE)
	text_bytes, err = p1.communicate()
	print(text_bytes.decode('utf-8'))

	p2 = subprocess.Popen(["cmake", "--build", "./dest"], stdout=subprocess.PIPE)
	text_bytes, err = p2.communicate()
	print(text_bytes.decode('utf-8'))

# Test opt
def testPass():
	p3 = subprocess.Popen(["opt", "-load", target_path, option_name, test_target_path])
	text_bytes, err = p3.communicate()

if args.testWay == "0":
	compile()
	testPass()
if args.testWay == "1":
	compile()
if args.testWay == "2":
	testPass()

# opt -load ./dest/libLLVMPointerCheck.so -pointer-check << ./HelloWorld.ll >> /dev/null