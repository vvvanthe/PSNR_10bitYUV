from glob import glob
import os
"""
    please, fit same formating in front of filename.
    "videoname_widthxheight......"
    
"""
def main():
    org_dir = './HEVC_yuv/or/1024x768'
    target_dir = './HEVC_yuv//1024x768'
    for org_file in glob(org_dir+'/*'):

        w,h = 1024 , 768
        filename=os.path.basename(org_file)
        path = os.path.dirname(org_file)
        folder_name = os.path.basename(path)
        target_file = target_dir+'/'+filename
        print('PSNRStatic.exe {} {} {} {}'.format(w, h, org_file, target_file))
        os.system('PSNRStatic.exe {} {} {} {}'.format(w, h, org_file, target_file))




if __name__ == "__main__":
    main()