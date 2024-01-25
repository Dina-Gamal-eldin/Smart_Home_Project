/*
 * utils.h
 *
 *  Created on: Nov 24, 2022
 *      Author: hikal
 */

#ifndef UTILS_H_
#define UTILS_H_

#define SET_BIT(Var,BitNo)      Var|=(1<<BitNo)
#define CLR_BIT(Var,BitNo)      Var&=(~(1<<BitNo))
#define TOGGLE_BIT(Var,BitNo)   Var^=(1<<BitNo)
#define GET_BIT(REG , BIT)     ((REG >> BIT) & 1)



#endif /* UTILS_H_ */
