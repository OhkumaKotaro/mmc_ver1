/**
  ******************************************************************************
  * File Name          : ADC.c
  * Description        : This file provides code for the configuration
  *                      of the ADC instances.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "adc.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */
#include "global.h"
/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
ADC_HandleTypeDef hadc3;

/* ADC1 init function */
void MX_ADC1_Init(void)
{
  ADC_ChannelConfTypeDef sConfig;

    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
    */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}
/* ADC2 init function */
void MX_ADC2_Init(void)
{
  ADC_ChannelConfTypeDef sConfig;

    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
    */
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc2.Init.Resolution = ADC_RESOLUTION_12B;
  hadc2.Init.ScanConvMode = DISABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion = 1;
  hadc2.Init.DMAContinuousRequests = DISABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}
/* ADC3 init function */
void MX_ADC3_Init(void)
{
  ADC_ChannelConfTypeDef sConfig;

    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
    */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc3.Init.Resolution = ADC_RESOLUTION_12B;
  hadc3.Init.ScanConvMode = DISABLE;
  hadc3.Init.ContinuousConvMode = DISABLE;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 1;
  hadc3.Init.DMAContinuousRequests = DISABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();
  
    /**ADC1 GPIO Configuration    
    PA4     ------> ADC1_IN4 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
  else if(adcHandle->Instance==ADC2)
  {
  /* USER CODE BEGIN ADC2_MspInit 0 */

  /* USER CODE END ADC2_MspInit 0 */
    /* ADC2 clock enable */
    __HAL_RCC_ADC2_CLK_ENABLE();
  
    /**ADC2 GPIO Configuration    
    PA0-WKUP     ------> ADC2_IN0
    PA3     ------> ADC2_IN3 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN ADC2_MspInit 1 */

  /* USER CODE END ADC2_MspInit 1 */
  }
  else if(adcHandle->Instance==ADC3)
  {
  /* USER CODE BEGIN ADC3_MspInit 0 */

  /* USER CODE END ADC3_MspInit 0 */
    /* ADC3 clock enable */
    __HAL_RCC_ADC3_CLK_ENABLE();
  
    /**ADC3 GPIO Configuration    
    PA1     ------> ADC3_IN1
    PA2     ------> ADC3_IN2 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN ADC3_MspInit 1 */

  /* USER CODE END ADC3_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();
  
    /**ADC1 GPIO Configuration    
    PA4     ------> ADC1_IN4 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4);

  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
  else if(adcHandle->Instance==ADC2)
  {
  /* USER CODE BEGIN ADC2_MspDeInit 0 */

  /* USER CODE END ADC2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC2_CLK_DISABLE();
  
    /**ADC2 GPIO Configuration    
    PA0-WKUP     ------> ADC2_IN0
    PA3     ------> ADC2_IN3 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0|GPIO_PIN_3);

  /* USER CODE BEGIN ADC2_MspDeInit 1 */

  /* USER CODE END ADC2_MspDeInit 1 */
  }
  else if(adcHandle->Instance==ADC3)
  {
  /* USER CODE BEGIN ADC3_MspDeInit 0 */

  /* USER CODE END ADC3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC3_CLK_DISABLE();
  
    /**ADC3 GPIO Configuration    
    PA1     ------> ADC3_IN1
    PA2     ------> ADC3_IN2 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1|GPIO_PIN_2);

  /* USER CODE BEGIN ADC3_MspDeInit 1 */

  /* USER CODE END ADC3_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
/****************************************************************************************
 * outline  : update battery(16bit) 
 * argument : void
 * return   : void
********************************************************************************************/
void update_batt_date(void)
{
  ADC_ChannelConfTypeDef sConfig;
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;
  HAL_ADC_ConfigChannel( &hadc1, &sConfig );  // setting store
  HAL_ADC_Start( &hadc1 );     // ad convert start
  while( HAL_ADC_PollForConversion( &hadc1,50 ) != HAL_OK );  // trans
  batt_analog=HAL_ADC_GetValue(&hadc1);
  HAL_ADC_Stop(&hadc1);
}

/****************************************************************************************
 * outline  : update front sensor
 * argument : void
 * return   : void
********************************************************************************************/
void update_fr_sen_on(void)
{
  ADC_ChannelConfTypeDef sConfig;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;

  sConfig.Channel = ADC_CHANNEL_0;
  HAL_ADC_ConfigChannel( &hadc2, &sConfig );  // setting store
  HAL_ADC_Start( &hadc2 );     // ad convert start
  while( HAL_ADC_PollForConversion( &hadc2,50 ) != HAL_OK );  // trans
  sensor.adc_on[0] = HAL_ADC_GetValue(&hadc2);
  HAL_ADC_Stop(&hadc2);

  sConfig.Channel = ADC_CHANNEL_3;
  HAL_ADC_ConfigChannel( &hadc2, &sConfig );  // setting store
  HAL_ADC_Start( &hadc2 );     // ad convert start
  while( HAL_ADC_PollForConversion( &hadc2,50 ) != HAL_OK );  // trans
  sensor.adc_on[3] = HAL_ADC_GetValue(&hadc2);
  HAL_ADC_Stop(&hadc2);
}


/****************************************************************************************
 * outline  : update battery 
 * argument : void
 * return   : void
********************************************************************************************/
void update_side_sen_on(void)
{
  ADC_ChannelConfTypeDef sConfig;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;

  sConfig.Channel = ADC_CHANNEL_1;
  HAL_ADC_ConfigChannel( &hadc3, &sConfig );  // setting store
  HAL_ADC_Start( &hadc3 );     // ad convert start
  while( HAL_ADC_PollForConversion( &hadc3,50 ) != HAL_OK );  // trans
  sensor.adc_on[1] = HAL_ADC_GetValue(&hadc3);
  HAL_ADC_Stop(&hadc3);

  sConfig.Channel = ADC_CHANNEL_2;
  HAL_ADC_ConfigChannel( &hadc3, &sConfig );  // setting store
  HAL_ADC_Start( &hadc3 );     // ad convert start
  while( HAL_ADC_PollForConversion( &hadc3,50 ) != HAL_OK );  // trans
  sensor.adc_on[2] = HAL_ADC_GetValue(&hadc3);
  HAL_ADC_Stop(&hadc3);
}

/****************************************************************************************
 * outline  : update front sensor value
 * argument : void
 * return   : void
********************************************************************************************/
void update_fr_sen_off(void)
{
  ADC_ChannelConfTypeDef sConfig;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;

  sConfig.Channel = ADC_CHANNEL_0;
  HAL_ADC_ConfigChannel( &hadc2, &sConfig );  // setting store
  HAL_ADC_Start( &hadc2 );     // ad convert start
  while( HAL_ADC_PollForConversion( &hadc2,50 ) != HAL_OK );  // trans
  sensor.adc_off[0] = HAL_ADC_GetValue(&hadc2);
  HAL_ADC_Stop(&hadc2);

  sConfig.Channel = ADC_CHANNEL_3;
  HAL_ADC_ConfigChannel( &hadc2, &sConfig );  // setting store
  HAL_ADC_Start( &hadc2 );     // ad convert start
  while( HAL_ADC_PollForConversion( &hadc2,50 ) != HAL_OK );  // trans
  sensor.adc_off[3] = HAL_ADC_GetValue(&hadc2);
  HAL_ADC_Stop(&hadc2);
}
/****************************************************************************************
 * outline  : update side sensor value
 * argument : void
 * return   : void
********************************************************************************************/
void update_side_sen_off(void)
{
  ADC_ChannelConfTypeDef sConfig;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;

  sConfig.Channel = ADC_CHANNEL_1;
  HAL_ADC_ConfigChannel( &hadc3, &sConfig );  // setting store
  HAL_ADC_Start( &hadc3 );     // ad convert start
  while( HAL_ADC_PollForConversion( &hadc3,50 ) != HAL_OK );  // trans
  sensor.adc_off[1] = HAL_ADC_GetValue(&hadc3);
  HAL_ADC_Stop(&hadc3);

  sConfig.Channel = ADC_CHANNEL_2;
  HAL_ADC_ConfigChannel( &hadc3, &sConfig );  // setting store
  HAL_ADC_Start( &hadc3 );     // ad convert start
  while( HAL_ADC_PollForConversion( &hadc3,50 ) != HAL_OK );  // trans
  sensor.adc_off[2] = HAL_ADC_GetValue(&hadc3);
  HAL_ADC_Stop(&hadc3);
}
/****************************************************************************************
 * outline  : update wall
 * argument : void
 * return   : void
********************************************************************************************/
void update_wall(void){
  for( int i=0;i<4;i++){
    sensor.adc[i] = sensor.adc_on[i] - sensor.adc_off[i];
  }
  
  if(sensor.adc[0] > threshhold_0){
    if(sensor.count[0] > 20){
      sensor.wall[0] = true;
    } else{
      sensor.count[0] ++;
    }
  }else{
    sensor.wall[0] = false;
    sensor.count[0] = 0;
  }
  
  if(sensor.adc[1] > threshhold_1){
    if(sensor.count[1] > 20){
      sensor.wall[1] = true;
    } else{
      sensor.count[1] ++;
    }
  }else{
    sensor.wall[1] = false;
    sensor.count[1] = 0;
  }

  if(sensor.adc[2] > threshhold_2){
    if(sensor.count[2] > 20){
      sensor.wall[2] = true;
    } else{
      sensor.count[2] ++;
    }
  }else{
    sensor.wall[2] = false;
    sensor.count[2] = 0;
  }

  if(sensor.adc[3] > threshhold_3){
    if(sensor.count[3] > 20){
      sensor.wall[3] = true;
    } else{
      sensor.count[3] ++;
    }
  }else{
    sensor.wall[3] = false;
    sensor.count[3] = 0;
  }
}
/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
