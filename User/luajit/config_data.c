#include <swilib.h>
#include <conf_loader.h>
#include <cfg_items.h>

/** ��������� ������� ��� ���
 * (�) Z.Vova
 */


__CFG_BEGIN(0)


__root CFG_HDR cfghdr0={CFG_CHECKBOX,"������������ stderr",0,2};
__root int _use_stderr = 1;


__root CFG_HDR cfghdr1={CFG_CHECKBOX,"������������ stdout",0,2};
__root int _use_stdout = 1;


__CFG_END(0)

/** ������ ������ �� config_data.c
  * Advanced -> Use custom command to build this file
  * ������ �������
  * ��������� ���� $compiler $options -xc $includes -c $file -o $object -O0
*/
