
## LLVM 분석기 연습문제 (Unreachable blocks)

#### 사전 준비: LLVM 소스 빌드
 - llvm.org에서 제안한 방법 (직접 Cmake 명령)으로 빌드하거나 이준영씨 스크립트를 활용하여 빌드
 - 이준영씨 빌드 스크립트를 활용하는 것을 가정
    * [https://github.com/aqjune/llvmscript](https://github.com/aqjune/llvmscript)
    * llvmscript를 사용하기 위한 설치 Prerequisites 명령어를 실행
        ~~~
        # Ubuntu
        $ apt update
        $ apt install git cmake ninja-build g++ python3-distutils zlib1g-dev libtinfo-dev libxml2-dev
        ~~~
   * llvmscript를 가져와서 이 디렉토리로 이동
        ~~~
        $ git clone https://github.com/aqjune/llvmscript
        $ cd llvmscript
        ~~~
   *  llvmscript를 llvm.json 파일을 인자로 지정하여 실행하여 llvm 소스를 클론
        ~~~
        $ python3 run.py clone --cfg examples/llvm.json 
        ~~~
      * 이때, llvm.json의 repo옵션을 수정해야 할 수도 있음
         ~~~
         "repo":"git@github.com:llvm/llvm-project.git"
         ==>
         "repo":"https://github.com/llvm/llvm-project.git"
         ~~~
   * llvmscript로 빌드 
         ~~~
         $ python3 run.py build --cfg examples/llvm.json --type release --core 6
         ~~~
   * 추가로 더 자세한 옵션이 있는데 필요하면 llvmscript 리포지토리에서 확인!

#### 문제: LLVM IR 프로그램을 입력받아 프로그램 시작 블록에서 도달하지 않는 블록(Unreachable block)을 모두 찾아 이름 순서로 나열하는 분석기 작성하기.
 - 서울대 허충길 교수의 <소프트웨어 개발의 원리와 실제> 과목의 3번 과제 3-2 소문제 
   * 문제: [https://github.com/snu-sf-class/swpp202001/tree/master/practice/3.assn](https://github.com/snu-sf-class/swpp202001/tree/master/practice/3.assn)
      - 문제에 대한 상세한 설명을 반드시 미리 읽을 것!
      ~~~
      [주어진 LLVM IR 프로그램]

      define void @f(i1 %cond) {
      entry:
        br i1 %cond, label %bb1, label %bb2
      bb1:
        br label %bb2
      bb2:
        ret void
      bb_unreachable:
        ret void
      }

      [결과]
      bb_unreachable
      ~~~
      
   * 참고: [https://github.com/snu-sf-class/swpp202001/tree/master/practice/3.materials](https://github.com/snu-sf-class/swpp202001/tree/master/practice/3.materials)
      - 특히, dump.cpp! 문제에 대한 해답과 거의 유사한 구조로 제시한 소스 파일.
      - 추가로 필요한 사항은 LLVM IR의 클래스 문서 (웹에서 참고)와 CPP 라이브러리 [http://cppreference.com](http://cppreference.com)
      
 - Step1: swpp202001 리포지토리리를 클론해서 내려 받고, 3번 과제 디렉토리로 이동
   ~~~
   $ git clone https://github.com/snu-sf-class/swpp202001
   $ cd snu-sf-class/swpp202001/practice/3.assn
   $ ls
    data-poly          package.sh        polygon.sh  unreachable.cpp
    data-unreachable   polygon.cpp       README.md   unreachable.sh
    libUnreachable.so  polygon_main.cpp  tmp
   ~~~
    * unreachable.cpp: 여러분이 완성시켜야할 소스 파일
    * unreachable.sh: 작성한 cpp 소스 파일을 컴파일하고 입력 데이터를 주어 채점하기 위한 쉘 파일
    * data-unreachable: 입력과 결과 데이터 파일
    
 - Step2: 아무 것도 작성하지 않았지만 일단 컴파일하고 실행시켜보기
    * all 옵션: 빌드하기 실행하기
    * build 옵션: 빌드만 하기
    * run 옵션: 실행만 하기
	  - (주의) ~/work/llvm/llvmscript/my-llvm-release/bin은 각자 빌드한 llvm의 bin 디렉토리로 바꾸어주어야 함
   ~~~
   $ ./unreachable.sh all ~/work/llvm/llvmscript/my-llvm-release/bin
   ~~~
    * unreachable.cpp을 처음 작성된 내용을 가지고 빌드하고 실행하면 모든 7가지 입력에 대해 모두 실패하여 0점을 받는다.

 - Step3: unreachable.cpp 작성하기
   * unreachable-sol.cpp과 같이 작성. 
   * 다시 all 옵션으로 빌드하고 실행하면 
   ~~~
   $ ./unreachable.sh all ~/work/llvm/llvmscript/my-llvm-release/bin  
   Testing data-unreachable/input1.ll..  
   Testing data-unreachable/input2.ll..  
   Testing data-unreachable/input3.ll..  
   Testing data-unreachable/input4.ll..  
   Testing data-unreachable/input5.ll..  
   Testing data-unreachable/input6.ll..  
   Testing data-unreachable/input7.ll..  
   Score: 70 / 70
   ~~~

#### 문제풀이:unreachable-sol.cpp에 대한 상세 설명
 - LLVM 프레임워크를 사용하여 분석기 패스(pass)를 모듈 방식으로 작성
   * MyUnreachablePass 클래스의 run 메소드만 구현하면 됨
   * run 메소드는 함수를 입력을 받아 (함수 단위의) 분석을 하는 구조를 가지고 있음
   * 도달 불가능한 블럭 분석 알고리즘 (unreachable-sol.cpp 소스 기준)
     - (1) (Line 41): 함수의 시작 블록 이름 entry 가져오기
     - (2) (Line 43-58): 함수의 각 블록에서 그 다음 블록들(successors)을 모두 모은 흐름 그래프 flowGraph 만들기 (추가로 모든 블록 이름들을 allBBs에 모으기)
        
       * (2-1) (Line 43): 함수의 각 블록을을 한 번씩 나열하고
       * (2-2) (Line 46): 현재 블록 이름을 currentBB로 가져오기
       * (2-3) (Line 48): 현재 블록 이름을 allBBs에 추가하기
       * (2-4) (Line 50-57): 현재 블록에서 분기할 수 있는 모든 successors 블록들을 모아 flowGraph에 (현재 블록->successor 블록) 에지(edge)를 추가하기
     - (3) (Line 60): 2단계에서 분석한 flow graph를 entry 블록에서 깊이 우선 탐색(depth-first search)으로 모든 도달 가능한 블록들을 마크하고 allBBs에 포함된 블록들 중에서 dfs 방문 마크되지 않은 블록들만 남긴다.)
	   * [dfs_block.png](//https://github.com/JNU-SoftwareLAB/LLVM-Tutorial/blob/master/examples/unreachable/dfs_blocks.png)
     - (4) (Line 62-65): allBBs에 dfs 방문 마크되지 않은 블록들을 하나씩 출력
       * allBBs의 타입은 std:set이고, 기본적으로 이름 순서로 정렬되어 있음






