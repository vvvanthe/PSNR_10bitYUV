from glob import glob
import os
"""
    please, fit same formating in front of filename.
    "videoname_widthxheight......"

"""
def main():
    org_dir = 'VVC_AI_ORG/'
    target_dir = 'VVC_Test/AI_L8_48_8_ver2/'
    bit = '10'
    for org_file in glob(target_dir+'/*/*'):
        path = os.path.dirname(org_file)

        folder_name = os.path.basename(path)
        target_file=org_dir+folder_name+'.yuv'
        #target_file = org_dir + folder_name+'/'+os.path.basename(org_file)# + '.yuv'
        w = 3840
        h = 2160
        #w = 1920
        #h = 1080
        #print('psnr10.exe {} {} {} {} {}'.format(w, h, bit, org_file, target_file))
        os.system('psnr10.exe {} {} {} {} {}'.format(w, h, bit, org_file, target_file))

if __name__ == "__main__":
    main()
