import hjson
import subprocess as sub

result = sub.check_output(['sensors', '-j'], universal_newlines=True)



print (result)
