//===-- HelloWorld.cpp - LLVM Tutorial Example ----------------------------===//
//
/// @file
/// This example explains very basical usage of Module and LLVMContext.
//
//===----------------------------------------------------------------------===//

#include <typeinfo>
#include <iostream>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"


#include "llvm/IR/DerivedTypes.h"

#include <system_error>
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Bitcode/BitcodeWriter.h"

#include "llvm/Support/ManagedStatic.h"

using namespace llvm;

int main()
{
  //===----------------------------------------------------------------------===//
  // Initializing LLVMContext, Module, IRBuilder
  //
  /// LLVMContext is like a thread context.
  /// this has states of a module.
  LLVMContext context;

  /// Modules are the top level container of all other LLVM
  /// Intermediate Representation (IR) objects.
  Module *module = new Module("hello", context);

  /// the IRBuilder helps to make IR codes with context.
  IRBuilder<> builder(context);

  //===----------------------------------------------------------------------===//
  // Declaring puts Function
  //
  /// puts function is external function and its' prototype is "i32 @puts(i8*)"
  /// this has arguments.
  std::vector<llvm::Type *> putsArgs;
  putsArgs.push_back(builder.getInt8Ty()->getPointerTo());
  ArrayRef<llvm::Type*> argsRef(putsArgs);
  
  /// Make FunctionType to make function prototype.
  /// and declare to module with FunctionType.
  FunctionType *putsType = FunctionType::get(builder.getInt32Ty(), argsRef, false);
  FunctionCallee putsFunc = module->getOrInsertFunction("puts", putsType);

  //===----------------------------------------------------------------------===//
  // Making Function and Basic Block
  //
  /// FunctionType::it is same with llvm::type::getInt32Ty(context)
  /// FunctionType::get is a static method for creating function.
  /// FunctionType::get always have return type and boolean value that describe this function has arguments
  /// if boolean value is treu, then second arguments have to come argument prototypes.
  FunctionType *funcType = FunctionType::get(builder.getInt32Ty(), false);
  
  /// Create Function with FunctionType and register it into Module.
  /// Function can't exist alone. it have to belong to a module.
  Function *mainFunc = Function::Create(funcType,
                                        Function::ExternalLinkage,
                                        "main", module);
  
  /// Create BasicBlock with static method.
  /// BasicBlock also can't exist alone. it have to belong to a function.
  BasicBlock *entry = BasicBlock::Create(context, "entrypoint", mainFunc);

  /// setInsertPoint as entry
  /// IRBuilder.CreateGlobalStringPtr related InsertPoint.
  /// so you have to use shortcut static method, IRBuilders' InsertPoint have to be entrypoint in function.
  builder.SetInsertPoint(entry);

  /// Global string value.
  /// if we create it by IRBuilder, then it also automatically register value into module.
  Value *hello_world = builder.CreateGlobalStringPtr("Hello World!\n");
  
  //===----------------------------------------------------------------------===//
  // Filling up BasicBlock of main function
  //
  /// We already set InsertPoint.
  /// putsFunc gets i8 pointer and hello_world is i8 type StringPtr.
  /// write function call into insert point.
  builder.CreateCall(putsFunc, hello_world);
  /// Make constant 0 and write ret 0 at basicBlock
  ConstantInt *const_int32  = ConstantInt::get( context , APInt(32, StringRef("0"), 10));
  builder.CreateRet(const_int32);


  //===----------------------------------------------------------------------===//
  // Writing Module into Bitcode file
  //
  /// get output stream
  std::error_code EC;
  raw_ostream *out = &outs();
  out = new raw_fd_ostream("hello.bc", EC, sys::fs::OF_None);

  /// make bc code
  WriteBitcodeToFile(*module, *out);
  /// write to file.
  out -> flush();

  module->dump();

  ///clean
  delete out;
  llvm_shutdown();
  
  return 0;
}