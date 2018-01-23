alias lss='screen -list'

export PS1="[\D{%d/%m/%y %R} \w]\n\$ "
export EDITOR="vim"
export SHELL=/bin/bash
export PAGER=less
# make bash append rather than overwrite the history on disk
shopt -s histappend
# Whenever displaying the prompt, write the previous line to disk
export PROMPT_COMMAND='history -a'
# set history file to be huge
export HISTSIZE=1000000000
# set history command limit to huge
export HISTFILESIZE=$HISTSIZE
# dont store these in history
export HISTIGNORE="c:ls:[bf]g:clear:exit"
alias launch-tf='docker run -it gcr.io/tensorflow/tensorflow bash'

r()
{
    vim -R $1
}
