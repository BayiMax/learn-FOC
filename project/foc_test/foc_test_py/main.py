import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from matplotlib import ticker

data = pd.read_csv("C:/Users/Bay_Max/Desktop/Learn/FOC/project/foc_test/foc_c++_test/cmake-build-debug/test_foc.csv")
save_picture = "./foc.png"  # 图片保存路径
xdata = data.loc[:, 'n']
A_ydata = data.loc[:, 'A']
B_ydata = data.loc[:, 'B']
C_ydata = data.loc[:, 'C']
# print(A_xdata)
# print(A_ydata)
plt.plot(xdata, A_ydata, color='b', label=u'A')
plt.plot(xdata, B_ydata, color='r', label=u'B')
plt.plot(xdata, C_ydata, color='g', label=u'C')
plt.title(u"A", size=10)  # 曲线标题

# 其中参数loc用于设置legend的位置，bbox_to_anchor用于在bbox_transform坐标（默认轴坐标）中为图例指定任意位置。
plt.legend(loc=1, bbox_to_anchor=(1.15, 1.0), borderaxespad=0)
plt.xlabel(u'x', size=10)
# 设置x轴标签旋转角度和字体大小
plt.xticks(rotation=10, fontsize=8)
plt.ylabel(u'out', size=10)
plt.gca().xaxis.set_major_locator(ticker.MultipleLocator(1000))  # 设置横坐标间隔（每隔80个横坐标显示一个横坐标，解决横坐标显示重叠问题）
plt.axhline(y=0.5, ls=":", c="gray")  # 添加水平辅助线
plt.axhline(y=0.55, ls=":", c="gray")  # 添加水平辅助线
plt.axhline(y=0.45, ls=":", c="gray")  # 添加水平辅助线
plt.savefig(save_picture)  # 保存图片
plt.show()
