cmd_/home/allen/Documents/Module.symvers := sed 's/\.ko$$/\.o/' /home/allen/Documents/modules.order | scripts/mod/modpost -m -a  -o /home/allen/Documents/Module.symvers -e -i Module.symvers   -T -
