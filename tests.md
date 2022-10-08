## This commands need to work before merging to develop :

- [ ] display /etc/passwd content
```
cat /etc/passwd
```

- [ ] display /etc/passwd root line
```
cat /etc/passwd | grep root
```

- [ ] add /etc/passwd root line to tmp file
```
cat /etc/passwd | grep root > /tmp/test-out
```

- [ ] Append /etc/passwd root line to tmp file
```
cat /etc/passwd | >> /tmp/test-out grep root 
```

- [ ] Get /etc/passwd as input file
```
< /etc/passwd cat -n
```

- [ ] Get /etc/passwd as input file other syntax
```
cat -n < /etc/passwd 
```

- [ ] display home path
```
echo "$HOME"
```

- [ ] display home path / editor
```
echo "$HOME/$EDITOR"
```

- [ ] T1 and T2 should be in env, 2T should display and error message
```
export T1=42 2T=42 T3=42
```

- [ ] T1 and T2 should not be in env anymore
```
unset T1 2T T3
```

- [ ] Get from stdin
```
<< EOF cat -n
```

- [ ] Get from stdin other syntax
```
cat -n << EOF1 << EOF2
```

- [ ] Test multiple redirections, should create all three out file and add the content of second << in out3
```
< /etc/passwd << EOF > /tmp/out1 cat -n > /tmp/out2 >/tmp/out3 << EOF
```

- [ ] Change directory
```
cd /tmp
```

- [ ] Should go to home
```
cd
```

