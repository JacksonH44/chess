## Git Commits
# Introduction
Git commits should be made after small, changes to a program that you know work as they should and will not introduce new bugs into the program. For example, after you complete a method for an object, you should make a commit.

# How to Make a Git Commit
1) Type <pre><code>git add filename</code><pre> to add <pre><code>filename</code></pre> to the staging area.
2) Type <pre><code>git status</code><pre> to see a list of current files in the staging area.
3) Once you are ready to make your commit, type <pre><code>git commit -m someMessage</code></pre>. The <pre><code>-m someMessage</code></pre> command allows you to add a commit message to your commit. You should always add a short, informative commit message to your commits, i.e. <pre><code>Implement Bishop::move</code></pre>.
4) After a larger objective is completed (i.e. a class is coded), you should push the changes to the remote repository. Do this by typing the command <pre><code>git push remote branch</code></pre>, which pushes the branch to the remote repository, along with all commits you have made.

# More information
Look at Git Cheatsheet.pdf for more information