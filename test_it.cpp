extern bool readState[8][8][2];
extern bool stateChange[8][8] = {{false, false, false, false, false, false, false, false},
                                 {false, false, false, false, false, false, false, false},
                                 {false, false, false, false, false, false, false, false},
                                 {false, false, false, false, false, false, false, false},
                                 {false, false, false, false, false, false, false, false},
                                 {false, false, false, false, false, false, false, false},
                                 {false, false, false, false, false, false, false, false},
                                 {false, false, false, false, false, false, false, false}};     


void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */
	//================================ Scan Board ================================//
    
	readState[7][7][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[7][6][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[7][5][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    readState[7][4][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[7][3][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[7][2][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[7][1][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    readState[7][0][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    
	readState[6][7][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[6][6][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[6][5][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    readState[6][4][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[6][3][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[6][2][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[6][1][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    readState[6][0][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    
	readState[5][7][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[5][6][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[5][5][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    readState[5][4][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[5][3][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[5][2][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[5][1][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    readState[5][0][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    
	readState[4][7][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[4][6][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[4][5][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    readState[4][4][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[4][3][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[4][2][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[4][1][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    readState[4][0][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
   
	readState[3][7][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[3][6][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[3][5][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    readState[3][4][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[3][3][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[3][2][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[3][1][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    readState[3][0][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    
	readState[2][7][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[2][6][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[2][5][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    readState[2][4][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[2][3][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[2][2][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[2][1][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    readState[2][0][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    
	readState[1][7][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[1][6][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[1][5][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    readState[1][4][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[1][3][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[1][2][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[1][1][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    readState[1][0][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    
	readState[0][7][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[0][6][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[0][5][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    readState[0][4][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[0][3][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[0][2][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
	readState[0][1][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    readState[0][0][1] = HAL_GPIO_ReadPin(GPIO, GPIO_PIN_);
    
  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */

  /* USER CODE END TIM4_IRQn 1 */
}