工作区-暂存区-版本库
git checkout -- [path]：撤销工作区的修改，可以指定文件。checkout其实是用版本库里的文件替换工作区的文件。
git add：工作区到暂存区
git commit：暂存区到版本库
git reset：三个级别
--soft重置版本库HEAD，暂存区不变
不加参数：重置HEAD并清空暂存区，工作区不变
--hard：重置HEAD并清空暂存区与工作区
