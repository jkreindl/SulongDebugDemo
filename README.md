# Sulong Debugging Demo

This repository contains sample projects to demonstrate cross-language debugging of C and Ruby code using [Sulong](https://github.com/graalvm/sulong) and [TruffleRuby](https://github.com/oracle/truffleruby). Both language implementations are part of the [GraalVM](https://www.graalvm.org/) project.

## Prerequisites

You can download the [latest GraalVM release from Oracle](https://www.graalvm.org/downloads/). Please also ensure that you have Clang and LLVM, including the `opt` tool available on your path. For a list of compatible versions please check [the Sulong README](https://github.com/graalvm/sulong). WAs we will use Chrome Devtools to debug the code, please make sure you have either [Google Chrome](https://www.google.com/chrome/) or [Chromium](https://www.chromium.org/Home) available.
