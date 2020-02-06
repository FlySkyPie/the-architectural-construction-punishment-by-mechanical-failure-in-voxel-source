#!/usr/bin/python3
# Thanks Yang,Wei-Jie helped, added parallel computing in visualize process (multiple thread). 
import os
import matplotlib.pyplot as plt
import csv
import numpy as np
import imageio    
from numpy import array
from matplotlib.font_manager import FontProperties
from multiprocessing import Process

myfont = FontProperties(fname=r'/usr/share/fonts/opentype/noto/NotoSansCJK-Thin.ttc',size=18)

def plot(data, frame, dataTitle):
    fig = plt.figure()
    #fig.suptitle('Time: '+str(frame))
    fig.suptitle(dataTitle,fontproperties=myfont)
    plt.imshow(data, cmap='magma')
    plt.ylim(0, 100)
    plt.colorbar()
    plt.savefig(str(frame).zfill(4) + ".png")
    plt.close()
    print(frame,end=',')

def createFrames(dataFile,dataTitle):
    frame=0
    jobs=[]
    with open(dataFile,'r') as dataFile:
        for row in dataFile.read().splitlines():
            pic = list(map(float, [data for data in row.split(',') if data]))
            nArray = array(pic)
            a11 = nArray.reshape(100,100)
            p = Process(target=plot, args=(a11, frame, dataTitle))
            jobs.append(p)
            p.start()
            frame+=1
    for p in jobs:
        p.join()
    print('')

def createGifs(datas, gifs):
    for data in datas:
        print('正在視覺化資料...')
        createFrames(data[0],data[1])
        print('正在建立動畫(gif)...')
        os.system("convert -delay 10 -loop 0 *.png " + data[0] + ".gif")
        gifs.append(imageio.get_reader(data[0] + ".gif"))
        os.system("rm *.png")

# @link https://stackoverflow.com/questions/51517685
def createFourViewGif(datas, gifs):
    #If they don't have the same number of frame take the shorter
    number_of_frames = gifs[0].get_length()
    for gif in gifs:
        if(number_of_frames<gif.get_length()):
            number_of_frames = gif.get_length()

    #Create writer object
    new_gif = imageio.get_writer('output.gif')

    print('正在合併動畫(gif)...')
    for frame_number in range(number_of_frames):
        imgs =[]
        for gif in gifs:
            imgs.append(gif.get_next_data()[:,60:560])
        #here is the magic
        rowImage1 = np.hstack([imgs[0],imgs[1]])
        rowImage2 = np.hstack([imgs[2],imgs[3]])
        new_image = np.vstack([rowImage1,rowImage2])
        new_gif.append_data(new_image)

    for gif in gifs:
        gif.close()
    new_gif.close() 

datas = [['data1.txt','原始重力流'],['data2.txt','修正項'],['data3.txt','修正值'],['data4.txt','方塊']]
gifs =[]
createGifs(datas, gifs)
createFourViewGif(datas, gifs)
