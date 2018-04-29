#！/usr/bin/env python
#-*- coding:utf-8 -*-
#author：Zisc
import os
import requests
import time
import random
from lxml import etree

keyWord = input(f"{'Please input the Keywords that you want to download:'}")
class Spider():
    #初始化函数
    def __init__(self):
        self.headers = {
            "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.104 Safari/537.36",
        }
        self.filePath = ('E:\\keyWord\photo')#这是我保存图片的路径名

    def creat_File(self):   #用os修改目标保存路径
        filePath = self.filePath
        if not os.path.exists(filePath): #判断路径是否存在，没有则创建
            os.makedirs(filePath)

    def get_pageNum(self):  #获取总页数
        total=""
        url = ("https://alpha.wallhaven.cc/search?q={}&categories=111&purity=100&sorting=relevance&order=desc").format(keyWord)
        html = requests.get(url).text
        selector = etree.HTML(html)
        pageInfo = selector.xpath('//header[@class="listing-header"]/h1[1]/text()')
        next_total = str(pageInfo[0])
        for item in next_total:
            if item.isdigit():
                total = total + item
        totalPagenum = int(total)
        return totalPagenum

    def getLinks(self,number):
        """
        获取图片的连接,
        这边的思路是先进入第一面爬取所有目标图片的请求链接，
        比如page为1的时候获取了第一页所有的图片的响应连接(但是这个连接并不是我们最终下载所需的连接),
        做for循环取出每一个响应连接再用xapth捉取最终下载连接(捉取得是//wallpapers.wallhaven.cc/wallpapers/full/wallhaven-399802.jpg)，
        所以在后面加上'https'拼接出完整的下载连接，存放在一个pic_downlist列表中。
        :param number:  *页
        :return:  返回该页上每一张图片响应链接后的真实下载url

        """
        url = ("https://alpha.wallhaven.cc/search?q={}&categories=111&purity=100&sorting=relevance&order=desc&page={}").format(keyWord,number)
        pic_downlist = []
        html = requests.get(url,headers=self.headers).text
        selector = etree.HTML(html)
        pic_Linklist = selector.xpath('//a[@class="jsAnchor thumb-tags-toggle tagged"]/@href')
        print(pic_Linklist) #打印该页所有图片的响应链接
        for item in pic_Linklist:
            html_in = requests.get(item,headers=self.headers).text
            selector_in = etree.HTML(html_in)
            pic_willdownlist = selector_in.xpath('//*[@id="wallpaper"]/@src')
            pic_get_url = "https:{}".format(str(pic_willdownlist[0]))
            pic_downlist.append(pic_get_url)
        return pic_downlist

    def download(self,url,count):
        """
        https://alpha.wallhaven.cc/网站上据我抽样点取，发现基本都是JPG,PNG格式的图片,

        demo："https://wallpapers.wallhaven.cc/wallpapers/full/wallhaven-635067.jpg"
              "https://wallpapers.wallhaven.cc/wallpapers/full/wallhaven-626126.png "
        要保存图片，必须就要在文件名上加上该格式得后缀，实在想不出办法只能出此愚见
        (
         在传入每一个该图片的url后做一个判断，判断该后缀后取出保存作为路径名
         )
        :param url: 在getLinks()上取得每一张图片响应链接后的真实url
        :param count: 第*张图片
        :return: None
        """
        if url.endswith('.jpg'):
            pic_path = (self.filePath + keyWord + str(count)+'.jpg')
        elif url.endswith('.png'):
            pic_path = (self.filePath + keyWord + str(count)+'.png')
        try:
            pic = requests.get(url, headers=self.headers)
            f = open(pic_path, 'wb')
            f.write(pic.content)
            f.close()
            print("Image:{} has been downloaded!".format(count))
            time.sleep(random.uniform(0, 2))
        except Exception as e:
            print(repr(e))

    def main_fuction(self):
         #count是图片总数，times是总页面数      
        self.creat_File()    #创建该工程保存目录
        count = self.get_pageNum()   #获得总图片数count
        print("We have found:{} images!".format(count)) #打印出来有多少张图片
        times = int(count / 24 + 1)#算出来有多少页
        j = 1
        for i in range(times):   #每一页开始遍历
            pic_Urls = self.getLinks(i + 1)  #获取第一页
            for item in pic_Urls:    #在第一页获取的响应连接逐个开始遍历
                self.download(item, j)  #调用下载函数传入item作为url，j用来计数
                j += 1
spider = Spider()
spider.main_fuction()
