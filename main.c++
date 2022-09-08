/*
 * @Author: iku50 wizo.o@outlook.com
 * @Date: 2022-07-29 00:34:40
 * @LastEditors: iku50 wizo.o@outlook.com
 * @LastEditTime: 2022-09-08 19:42:11
 * @FilePath: /我的坚果云/AST/main.c++
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "src/src.c++"
#include "src/ASTgenerate.c++"
string token_text[99];
int p =0;
int tab=0;
token_kind token_type =NU;
fun func[20];
int func_num=0;
int main(int argc,char **argv){
    Start(argc,argv);
    return 0;
}