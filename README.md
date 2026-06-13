# Preparation-for-the-provincial-electronic-competition

电赛备赛练习

## 组别文件夹

| 组别 | 文件夹名 |
|------|---------|
| 蔡晓越组 | `蔡晓越组/` |
| 张兆喆组 | `张兆喆组/` |
| 徐博涵组 | `徐博涵组/` |
| 邱照宇组 | `邱照宇组/` |
| 朱则熹组 | `朱则熹组/` |
| 张锐涛组 | `张锐涛组/` |

## 准备工作（只需一次）

1. 在电脑上安装 [Git](https://git-scm.com/download/win)（Windows 用户下载后一路默认安装即可）
2. 注册 [GitHub](https://github.com) 账号并告诉我用户名，我把你添加为仓库协作者

## 首次操作：克隆仓库到本地

打开终端（CMD / PowerShell / Git Bash），执行：

```bash
git clone https://github.com/aaaaawwaa/Preparation-for-the-provincial-electronic-competition.git
cd Preparation-for-the-provincial-electronic-competition
```

> 如果连接失败，可能是代理问题，换成以下命令：
> ```bash
> git -c http.proxy= -c https.proxy= clone https://github.com/aaaaawwaa/Preparation-for-the-provincial-electronic-competition.git
> ```

---

## 方式一：自动上传脚本（推荐）

1. 用记事本/VSCode 打开仓库中的 `upload.sh`
2. 修改顶部四个变量：

```bash
TEAM="张锐涛组"                              # 你的组别文件夹名
PROJECT_PATH="C:/Users/.../你的工程路径"      # 要上传的工程路径
COMMIT_MSG="上传XXX工程"                      # 提交说明
REPO_DIR="C:/Users/.../Preparation-for-the-provincial-electronic-competition"  # 仓库本地路径
```

3. 在终端运行：

```bash
bash upload.sh
```

脚本会自动完成同步 → 复制 → 提交 → 推送。

---

## 方式二：手动上传

### 第1步：同步最新代码

```bash
cd Preparation-for-the-provincial-electronic-competition
git pull origin main
```

> 如果 pull 失败加代理参数：`git -c http.proxy= -c https.proxy= pull origin main`

### 第2步：把自己的工程文件放入对应组别文件夹

**注意：只在自己的组别文件夹里操作，不要动其他组的文件**

### 第3步：提交并推送

```bash
git add "你的组别文件夹名/"
git commit -m "XX组 - 上传XXX工程"
git push origin main
```

> 如果 push 失败：`git -c http.proxy= -c https.proxy= push origin main`

---

## 完整示例（张兆喆组为例）

```bash
cd Preparation-for-the-provincial-electronic-competition
git pull origin main
cp -r ~/自己工程文件夹路径/* 张兆喆组/
git add 张兆喆组/
git commit -m "张兆喆组 - 上传2ASK调制工程"
git push origin main
```

---

## 常见问题

**Q：push 时提示 "Updates were rejected"？**  
A：说明远程仓库有别人的新提交，先执行 `git pull origin main` 同步后再 push。

**Q：提示 "Permission denied"？**  
A：你的 GitHub 账号还没有被添加为仓库协作者，把用户名发给我。

**Q：连接一直失败？**  
A：执行命令时在 `git` 后面加上 `-c http.proxy= -c https.proxy=` 来绕过本地代理。
