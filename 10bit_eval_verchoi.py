from glob import glob
import os
"""
    please, fit same formating in front of filename.
    "videoname_widthxheight......"

"""
def main():
    org_dir = './ORG_10bit'
    target_dir = './TEST_10bit'
    bit = '10'
    for org_file in glob(org_dir+'/*'):
        fname,size,_ = org_file.split('\\')[1].split('_')
        w,h = size.split('x')
        for target_file in glob(target_dir+'/*'):
            tname = target_file.split('\\')[1].split('_')[0]
            if fname == tname:
                print('psnr10.exe {} {} {} {} {}'.format(w,h,bit,org_file,target_file))
                os.system('psnr10.exe {} {} {} {} {}'.format(w,h,bit,org_file,target_file))

if __name__ == "__main__":
    main()
