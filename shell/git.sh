#!/bin/bash

rm -rf git 
mkdir git 
cd git 

git init

echo "Hello Git" >test.txt

git add test.txt
git commit -m "2015/08/12 17:30"

git remote add origin ssh://edu@10.221.2.62/home/edu/git/.git
git push origin master