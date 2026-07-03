[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/ChdUsKnR)
# myenvプログラムの作成

```env```コマンドのクローン```myenv```プログラムを作りなさい．

### 作成
1. myenvの仕様<br>
envは環境変数を変更した上でプログラム（コマンド）を実行する．<br>
```env [name=value ...] [command [argument ...]]```<br>
```name=value```形式の文字列は環境変数の変更を指示する．<br>
```command [argument ...]```は実行するプログラム（コマンド）と引数である．<br>
```command [argument ...]```部分を省略すると変更後の環境変数一覧を表示する．

2. myenvプログラムの作成<br>
レポジトリをクローンし```myenv.c```を編集してプログラムを完成する．<br>
上の仕様を満たすプログラムを美しくコーディングする．<br>
できたと思ったら十分な動作テストを行う．

### コンパイル方法
```Makefile```を準備してあるので```make```コマンドでコンパイルできる．

```
$ make
cc -D_GNU_SOURCE -Wall -std=c99 -o myenv myenv.c myputenv.c
$
```
