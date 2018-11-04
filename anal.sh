#!/bin/bash

source /etc/profile

llvm-profdata merge -sparse bld/CTRLV.profraw -o CTRLV.profdata
llvm-cov show bld/test/CTRLV -instr-profile=CTRLV.profdata -format=html -output-dir=bld/cov
llvm-cov export test/CTRLV -instr-profile=CTRLV.profdata > cov.json
if [ ! -f bld/Coverify.jar ]; then 
    wget https://github.com/Olipro/Coverify/releases/download/v0.1.0/Coverify-1.0-SNAPSHOT.jar -O bld/Coverify.jar
fi
~/bins/jdk-11.0.1/bin/java -jar bld/Coverify.jar cov.json > cov.xml
mv bld/report.xml .
~/bins/sonar-scanner/bin/sonar-scanner -Dproject.settings=sonarqube.properties
