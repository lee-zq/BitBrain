# 1. 使用top命令将指定进程的系统监控数据写入文件
# top -b -d 1 -p $PID| grep $PID > mem.txt 

# 2. python绘制资源占用情况图

import matplotlib.pyplot as plt
import matplotlib.pylab as pylab
import os, sys
from os.path import join
from collections import OrderedDict
import numpy as np

params = {'legend.fontsize': 12,
         'axes.labelsize': 15,
         'axes.titlesize':15,
         'xtick.labelsize':13,
         'ytick.labelsize':13} # define pyplot parameters
pylab.rcParams.update(params)
plt.switch_backend('agg')
plt.rcParams["figure.figsize"]= [32,6]
plt.grid()

def parser_file(file_path):
    virt_lst = []
    res_lst = []
    shr_lst = []
    cpu_lst = []
    pid = 0
    user = "None"
    command = "None"
    with open(file_path, "r") as f:
        lines = f.readlines()
        exe_info = lines[0].split()
        pid = exe_info[0]
        user = exe_info[1]
        command = " ".join(exe_info[11:])

        for line in lines:
            if line[-1]=="\n": line = line[:-1]
            values = line.split()
            if len(values)!=len(exe_info):
                continue
            virt_lst.append(values[4])
            res_lst.append(values[5])
            shr_lst.append(values[6])
            cpu_lst.append(values[8])
    return virt_lst, res_lst, shr_lst, cpu_lst

def draw_picture(file_path):
    file_name = file_path.split("/")[-1].split(".")[0]
    virt_lst, res_lst, shr_lst, cpu_lst =  parser_file(file_path)
    plot_dict = [
        ("CPU Cost",cpu_lst),
        ("Physical Memory",res_lst),
        ("Virtual Memory",virt_lst),
        ("Shared Memory",shr_lst)
    ]
    fig, ax = plt.subplots(nrows = 1, ncols = 4)
    for i in range(len(plot_dict)):
        name,data = plot_dict[i]
        x_lst = list(range(len(data)))
        if data[0][-1].isalpha():
            symbol = data[0][-1]
        else:
            symbol = ""
        y_lst = [float(i.replace(symbol, "")) for i in data]

        min_value = min(y_lst)
        max_value = max(y_lst)
        mean_value = round(sum(y_lst)/len(y_lst), 4)
        ax[i].plot(x_lst,y_lst)
        ax[i].grid()
        ax[i].legend([name + f"\nAvg:{mean_value}\nMax:{max_value}\nMin:{min_value}"])
        ax[i].set_title(name + "/" + symbol)
    plt.savefig(file_path.split(".")[0] + ".png")

if __name__=="__main__":
    draw_picture("/root/project/lzq/BitBrain/mem.txt")