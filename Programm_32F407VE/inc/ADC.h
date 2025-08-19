#ifndef ADC_H_
#define ADC_H_

/*includes*/
#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include "HEHAL.h"
#include "GPIO.h"
#include <stdio.h>

/*defaines*/

/*RM0090 Reference manual STM32F405/415, STM32F407/417, STM32F427/437 and STM32F429/439*/
/*13.13 ADC registers*/
/*13.13.1 Регистр состояния АЦП (ADC_SR) Address offset: 0x00*/
#define ADC_SR_Pos 0x00
#define ADC_AWD (0x1 << 0) /*Читаем: Аналоговый флаг сторожевого таймера*/
#define ADC_EOC (0x1 << 1) /*Читаем: Окончание преобразования обычного канала*/
#define ADC_JEOC (0x1 << 2) /*Читаем: Этот бит устанавливается аппаратно в конце преобразования всех инжектированных каналов в группе*/
#define ADC_JSTRT (0x1 << 3) /*Читаем: Этот бит устанавливается аппаратно при запуске преобразования инжектированной группы*/
#define ADC_STRT (0x1 << 4) /*Читаем: Этот бит устанавливается аппаратно при запуске обычного преобразования каналов*/
#define ADC_OVR (0x1 << 5) /*Читаем:  Переполнение*/

/*13.13.2 Регистр управления 1 АЦП  (ADC_CR1) Address offset: 0x04*/
#define ADC_CR1_Pos 0x04
#define ADC_CR1_AWDCH0 (0x00000 << 0)/*Выбора канала аналогового сторожевого таймера*/
#define ADC_CR1_AWDCH1 (0x00001 << 0)/*Выбора канала аналогового сторожевого таймера*/
#define ADC_CR1_AWDCH2 (0x00010 << 0)/*Выбора канала аналогового сторожевого таймера*/
#define ADC_CR1_AWDCH3 (0x00011 << 0)/*Выбора канала аналогового сторожевого таймера*/
#define ADC_CR1_AWDCH4 (0x00100 << 0)/*Выбора канала аналогового сторожевого таймера*/
#define ADC_CR1_AWDCH5 (0x00101 << 0)/*Выбора канала аналогового сторожевого таймера*/
#define ADC_CR1_AWDCH6 (0x00110 << 0)/*Выбора канала аналогового сторожевого таймера*/
#define ADC_CR1_AWDCH7 (0x00111 << 0)/*Выбора канала аналогового сторожевого таймера*/
#define ADC_CR1_AWDCH8 (0x01000 << 0)/*Выбора канала аналогового сторожевого таймера*/
#define ADC_CR1_AWDCH9 (0x01001 << 0)/*Выбора канала аналогового сторожевого таймера*/
#define ADC_CR1_AWDCH10 (0x01010 << 0)/*Выбора канала аналогового сторожевого таймера*/
#define ADC_CR1_AWDCH11 (0x01011 << 0)/*Выбора канала аналогового сторожевого таймера*/
#define ADC_CR1_AWDCH12 (0x01100 << 0)/*Выбора канала аналогового сторожевого таймера*/
#define ADC_CR1_AWDCH13 (0x01101 << 0)/*Выбора канала аналогового сторожевого таймера*/
#define ADC_CR1_AWDCH14 (0x01110 << 0)/*Выбора канала аналогового сторожевого таймера*/
#define ADC_CR1_AWDCH15 (0x01111 << 0)/*Выбора канала аналогового сторожевого таймера*/
//#define ADC_CR1_EOCIE (0x1 << 5) /*Разрешение прерывания для EOC*/
//#define ADC_CR1_AWDIE (0x1 << 6) /* Разрешение прерывания аналогового сторожевого таймера*/
//#define ADC_CR1_JEOCIE (0x1 << 7) /*Разрешение прерывания для инжектированных каналов*/
//#define ADC_CR1_SCAN (0x1 << 8) /* В режиме сканирования преобразуются входные сигналы, выбранные через регистры ADC_SQRx или ADC_JSQRx.*/
//#define ADC_CR1_AWDSGL (0x1 << 9) /*Включение сторожевого таймера на одном канале в режиме сканирования*/
//#define ADC_CR1_JAUTO (0x1 << 10) /* Автоматическое преобразование инжектированной группы*/
//#define ADC_CR1_DISCEN (0x1 << 11) /* Прерывистый режим на обычных каналах*/
//#define ADC_CR1_JDISCEN (0x1 << 12) /* Прерывистый режим на инжектированных каналах*/
#define ADC_CR1_DISCNUM1 (0x000 << 13)/*Количество каналов в прерывистом режиме*/
#define ADC_CR1_DISCNUM2 (0x001 << 13)/*Количество каналов в прерывистом режиме*/
#define ADC_CR1_DISCNUM3 (0x010 << 13)/*Количество каналов в прерывистом режиме*/
#define ADC_CR1_DISCNUM4 (0x011 << 13)/*Количество каналов в прерывистом режиме*/
#define ADC_CR1_DISCNUM5 (0x100 << 13)/*Количество каналов в прерывистом режиме*/
#define ADC_CR1_DISCNUM6 (0x101 << 13)/*Количество каналов в прерывистом режиме*/
#define ADC_CR1_DISCNUM7 (0x110 << 13)/*Количество каналов в прерывистом режиме*/
#define ADC_CR1_DISCNUM8 (0x111 << 13)/*Количество каналов в прерывистом режиме*/
//#define ADC_CR1_JAWDEN (0x1 << 22) /*Включение аналогового сторожевого таймера на инжектированных каналах*/
//#define ADC_CR1_AWDEN (0x1 << 23) /*Включение аналогового сторожевого таймера на обычных каналах*/
#define ADC_CR1_RES_12bit (0x00 << 24)/*Разрешения преобразования, 15 циклов ADCCLK*/
#define ADC_CR1_RES_10bit (0x01 << 24)/*Разрешения преобразования, 13 циклов ADCCLK*/
#define ADC_CR1_RES_8bit (0x10 << 24)/*Разрешения преобразования, 11 циклов ADCCLK*/
#define ADC_CR1_RES_6bit (0x11 << 24)/*Разрешения преобразования, 9 циклов ADCCLK*/
//#define ADC_CR1_OVRIE (0x1 << 26) /*Разрешение прерывания переполнения*/

/*13.13.3 Регистр управления 2 АЦП  (ADC_CR2) Address offset: 0x08*/
#define ADC_CR2_Pos 0x08
//#define ADC_CR2_ADON (0x1 << 0) /*АЦП ВКЛ/ВЫКЛ*/
//#define ADC_CR2_CONT (0x1 << 1) /*Непрерывное преобразование*/
//#define ADC_CR2_DMA (0x1 << 8) /*режим прямого доступа к памяти (для режима одного АЦП)*/
//#define ADC_CR2_DDS (0x1 << 9) /*Запросы DMA выдаются, пока данные преобразуются (для режима одного АЦП)*/
//#define ADC_CR2_EOCS (0x1 << 10) /*Выбор конца преобразования, Бит EOC устанавливается в конце каждого обычного преобразования*/
//#define ADC_CR2_ALIGN (0x1 << 11) /*выравнивание данных, 0: Выравнивание по правому краю , 1: Выравнивание по левому краю*/



#define ADC_SOFTWARE_START             ((uint32_t)ADC_CR2_EXTSEL + 1U)
#define ADC_COMMON_REGISTER(__HANDLE__)                ADC123_COMMON
#define ADC_STAB_DELAY_US               3U /* Задержка времени стабилизации АЦП*/
#define ADC_SQR3_RK(_CHANNELNB_, _RANKNB_) (((uint32_t)((uint16_t)(_CHANNELNB_))) << (5U * ((_RANKNB_) - 1U)))/* Установите выбранный обычный ранг канала в диапазоне от 1 до 6.*/
#define ADC_SQR2_RK(_CHANNELNB_, _RANKNB_) (((uint32_t)((uint16_t)(_CHANNELNB_))) << (5U * ((_RANKNB_) - 7U)))/* Установите выбранный обычный ранг канала в диапазоне от 7 до 12.*/
#define ADC_SQR1_RK(_CHANNELNB_, _RANKNB_) (((uint32_t)((uint16_t)(_CHANNELNB_))) << (5U * ((_RANKNB_) - 13U)))/* Установите выбранный обычный ранг канала в диапазоне от 13 и 16.*/
#define ADC_CR1_SCANCONV(_SCANCONV_MODE_) ((_SCANCONV_MODE_) << 8U)/*Включить режим сканирования АЦП*/
#define ADC_CR2_CONTINUOUS(_CONTINUOUS_MODE_) ((_CONTINUOUS_MODE_) << 1U)/*Включить режим непрерывного преобразования АЦП*/
#define ADC_CR1_DISCONTINUOUS(_NBR_DISCONTINUOUSCONV_) (((_NBR_DISCONTINUOUSCONV_) - 1U) << ADC_CR1_DISCNUM_Pos)/*Настраивает количество прерывистых преобразований для обычных групповых каналов.*/
#define ADC_CR2_DMAContReq(_DMAContReq_MODE_) ((_DMAContReq_MODE_) << 9U)/*Включить непрерывный запрос ADC DMA.*/
#define ADC_CR2_EOCSelection(_EOCSelection_MODE_) ((_EOCSelection_MODE_) << 10U)/*Включить выбор конца преобразования АЦП.*/
#define ADC_CHANNEL_TEMPSENSOR  ((uint32_t)ADC_CHANNEL_16)/*Каналы для АЦП*/
#define ADC_SQR1(_NbrOfConversion_) (((_NbrOfConversion_) - (uint8_t)1U) << 20U)

/*Общие каналы АЦП*/ 
#define ADC_CHANNEL_0           0x00000000U
#define ADC_CHANNEL_1           ((uint32_t)ADC_CR1_AWDCH_0)
#define ADC_CHANNEL_2           ((uint32_t)ADC_CR1_AWDCH_1)
#define ADC_CHANNEL_3           ((uint32_t)(ADC_CR1_AWDCH_1 | ADC_CR1_AWDCH_0))
#define ADC_CHANNEL_4           ((uint32_t)ADC_CR1_AWDCH_2)
#define ADC_CHANNEL_5           ((uint32_t)(ADC_CR1_AWDCH_2 | ADC_CR1_AWDCH_0))
#define ADC_CHANNEL_6           ((uint32_t)(ADC_CR1_AWDCH_2 | ADC_CR1_AWDCH_1))
#define ADC_CHANNEL_7           ((uint32_t)(ADC_CR1_AWDCH_2 | ADC_CR1_AWDCH_1 | ADC_CR1_AWDCH_0))
#define ADC_CHANNEL_8           ((uint32_t)ADC_CR1_AWDCH_3)
#define ADC_CHANNEL_9           ((uint32_t)(ADC_CR1_AWDCH_3 | ADC_CR1_AWDCH_0))
#define ADC_CHANNEL_10          ((uint32_t)(ADC_CR1_AWDCH_3 | ADC_CR1_AWDCH_1))
#define ADC_CHANNEL_11          ((uint32_t)(ADC_CR1_AWDCH_3 | ADC_CR1_AWDCH_1 | ADC_CR1_AWDCH_0))
#define ADC_CHANNEL_12          ((uint32_t)(ADC_CR1_AWDCH_3 | ADC_CR1_AWDCH_2))
#define ADC_CHANNEL_13          ((uint32_t)(ADC_CR1_AWDCH_3 | ADC_CR1_AWDCH_2 | ADC_CR1_AWDCH_0))
#define ADC_CHANNEL_14          ((uint32_t)(ADC_CR1_AWDCH_3 | ADC_CR1_AWDCH_2 | ADC_CR1_AWDCH_1))
#define ADC_CHANNEL_15          ((uint32_t)(ADC_CR1_AWDCH_3 | ADC_CR1_AWDCH_2 | ADC_CR1_AWDCH_1 | ADC_CR1_AWDCH_0))
#define ADC_CHANNEL_16          ((uint32_t)ADC_CR1_AWDCH_4)
#define ADC_CHANNEL_17          ((uint32_t)(ADC_CR1_AWDCH_4 | ADC_CR1_AWDCH_0))
#define ADC_CHANNEL_18          ((uint32_t)(ADC_CR1_AWDCH_4 | ADC_CR1_AWDCH_1))

#define ADC_CHANNEL_VREFINT     ((uint32_t)ADC_CHANNEL_17)
#define ADC_CHANNEL_VBAT        ((uint32_t)ADC_CHANNEL_18)

/*Установите время выборки АЦП для каналов с номерами от 10 до 18._SAMPLETIME_ Параметр времени выборки._CHANNELNB_ Channel number.*/
#define ADC_SMPR1(_SAMPLETIME_, _CHANNELNB_) ((_SAMPLETIME_) << (3U * (((uint32_t)((uint16_t)(_CHANNELNB_))) - 10U)))
#define ADC_SMPR2(_SAMPLETIME_, _CHANNELNB_) ((_SAMPLETIME_) << (3U * ((uint32_t)((uint16_t)(_CHANNELNB_)))))

/*Определение флагов АЦП*/
#define ADC_FLAG_AWD    ((uint32_t)ADC_SR_AWD)
#define ADC_FLAG_EOC    ((uint32_t)ADC_SR_EOC)
#define ADC_FLAG_JEOC   ((uint32_t)ADC_SR_JEOC)
#define ADC_FLAG_JSTRT  ((uint32_t)ADC_SR_JSTRT)
#define ADC_FLAG_STRT   ((uint32_t)ADC_SR_STRT)
#define ADC_FLAG_OVR    ((uint32_t)ADC_SR_OVR)

/*Определение прерываний АЦП*/
#define ADC_IT_EOC      ((uint32_t)ADC_CR1_EOCIE)
#define ADC_IT_AWD      ((uint32_t)ADC_CR1_AWDIE)
#define ADC_IT_JEOC     ((uint32_t)ADC_CR1_JEOCIE)
#define ADC_IT_OVR      ((uint32_t)ADC_CR1_OVRIE)

/*structures*/
typedef struct
{
  uint32_t ClockPrescaler;               /*Выберите предделитель тактовой частоты АЦП. Тактовая частота общая для
                                            всех АЦП.
                                            Этот параметр может иметь значение @ref ADC_ClockPrescaler */
  uint32_t Resolution;                   /*Настраивает разрешение АЦП.
                                            Этот параметр может иметь значение @ref ADC_Resolution. */
  uint32_t DataAlign;                    /*Задаёт выравнивание данных АЦП по правому краю (старший значащий бит в 11-м бите регистра и младший значащий бит в 0-м бите регистра) (настройка по умолчанию)
                                            или по левому краю (для обычной группы: старший значащий бит в 15-м бите регистра и младший значащий бит в 4-м бите регистра, для инжектированной группы (старший значащий бит сохраняется как знаковое значение из-за потенциально отрицательного значения после применения смещения): старший значащий бит в 14-м бите регистра и младший значащий бит в 3-м бите регистра).
                                            Этот параметр может быть значением @ref ADC_Data_align */
  uint32_t ScanConvMode;                 /*Настраивает секвенсор обычных и инжектированных групп.
                                            Этот параметр можно связать с параметром «DiscontinuousConvMode», чтобы основная последовательность была разделена на последовательные части.
                                            Если отключено: преобразование выполняется в одиночном режиме (преобразуется один канал, определенный в ранге 1).
                                            Параметры «NbrOfConversion» и «InjectedNbrOfConversion» отбрасываются (эквивалентно значению 1).
                                            Если включено: преобразования выполняются в последовательном режиме (несколько рангов, определенных параметрами «NbrOfConversion»/«InjectedNbrOfConversion» и рангом каждого канала).
                                            Направление сканирования — восходящее: от ранга 1 к рангу «n».
                                            Этот параметр можно установить в значения «ВКЛЮЧЕНО» или «ОТКЛЮЧЕНО». */
  uint32_t EOCSelection;                 /*Указывает, какой флаг EOC (End Of Conversion) используется для преобразования с помощью опроса и прерывания: конец преобразования каждого ранга или полная последовательность.
                                            Этот параметр может быть значением @ref ADC_EOCSelection.
                                            Примечание: Для инжектируемой группы сигнал окончания преобразования (flag&IT) активируется только в конце последовательности.
                                            Следовательно, если конец преобразования установлен на конец каждого преобразования, инжектируемую группу не следует использовать с прерыванием (HAL_ADCEx_InjectedStart_IT)
                                            или опросом (HAL_ADCEx_InjectedStart и HAL_ADCEx_InjectedPollForConversion). Опрос по-прежнему возможен, поскольку драйвер будет использовать предполагаемое время окончания инжектируемого преобразования. Примечание: Если предполагается использование функции переполнения, используйте АЦП в режиме «прерывание» (функция HAL_ADC_Start_IT()) с параметром EOCSelection, установленным на конец каждого преобразования, или в режиме «передача по DMA» (функция HAL_ADC_Start_DMA()).
                                            Если предполагается обход функции переполнения, используйте АЦП в режиме «опрос» или «прерывание», при этом параметр EOCSelection должен быть установлен на конец последовательности. */
  FunctionalState ContinuousConvMode;    /*Указывает, выполняется ли преобразование в одиночном режиме (одно преобразование) или непрерывно для обычной группы,
                                            после срабатывания выбранного триггера (запуск программы или внешний триггер).
                                            Этот параметр может быть установлен на ВКЛЮЧЕНО или ОТКЛЮЧЕНО. */
  uint32_t NbrOfConversion;              /*Указывает количество рангов, которые будут преобразованы в рамках обычного группового секвенсора.
                                            Чтобы использовать обычный групповой секвенсор и преобразовать несколько рангов, необходимо включить параметр «ScanConvMode».
                                            Этот параметр должен быть числом в диапазоне от Min_Data = 1 до Max_Data = 16. */
  FunctionalState DiscontinuousConvMode; /*Определяет, выполняется ли последовательность преобразований обычной группы в режиме Complete-sequence/Discontinuous-sequence (основная последовательность, разделенная на последовательные части).
                                            Прерывистый режим используется только при включенном секвенсоре (параметр ScanConvMode). Если секвенсор отключен, этот параметр отменяется.
                                            Прерывистый режим может быть включен только при отключенном непрерывном режиме. Если включен непрерывный режим, этот параметр отменяется.
                                            Этот параметр может быть установлен в значение ENABLE (ВКЛЮЧЕНО) или DISABLE (ОТКЛЮЧЕНО). */
  uint32_t NbrOfDiscConversion;          /* Задаёт количество дискретных преобразований, на которые будет разделена основная последовательность обычной группы (параметр NbrOfConversion).
                                            Если параметр DiscontinuousConvMode отключён, этот параметр отбрасывается.
                                            Значение этого параметра должно быть числом в диапазоне от Min_Data = 1 до Max_Data = 8. */
  uint32_t ExternalTrigConv;             /* Выбирает внешнее событие, используемое для запуска преобразования обычной группы.
                                            Если установлено значение ADC_SOFTWARE_START, внешние триггеры отключены.
                                            Если установлено значение внешнего источника триггера, триггер по умолчанию срабатывает по переднему фронту события.
                                            Этот параметр может иметь значение @ref ADC_External_trigger_Source_Regular */
  uint32_t ExternalTrigConvEdge;         /*Выбирает внешний фронт запуска обычной группы.
                                            Если задано значение ADC_SOFTWARE_START, этот параметр отбрасывается.
                                            Этот параметр может иметь значение @ref ADC_External_trigger_edge_Regular */
  FunctionalState DMAContinuousRequests; /*Указывает, выполняются ли запросы DMA в режиме однократного выполнения (передача DMA останавливается при достижении заданного количества преобразований)
                                          или в непрерывном режиме (передача DMA не ограничена, независимо от количества преобразований).
                                          Примечание: В непрерывном режиме DMA должен быть настроен на циклический режим. В противном случае при достижении указателя максимального значения буфера DMA будет срабатывать переполнение.
                                          Примечание: Этот параметр необходимо изменять, когда преобразования не выполняются ни в обычной, ни в инжектированной группе (АЦП отключен или АЦП включен без непрерывного режима или внешнего триггера, который мог бы запустить преобразование).
                                          Этот параметр может быть установлен в значение «ВКЛЮЧЕНО» (ENABLE) или «ОТКЛЮЧЕНО» (DISABLE) */
} ADC_Init_TypeDef;

typedef struct
{
  ADC_TypeDef *Instance; /*Зарегистрировать базовый адрес */

  ADC_Init_TypeDef Init; /*Требуемые параметры АЦП */

  uint32_t NbrOfCurrentConversionRank; /*Номер АЦП текущего ранга преобразования*/

  //DMA_HandleTypeDef *DMA_Handle; /*Обработчик указателя DMA */

  uint32_t Channel;      /*Указывает канал для настройки в обычной группе АЦП.
                            Этот параметр может иметь значение @ref ADC_channels */
  uint32_t Rank;         /*Указывает ранг в секвенсоре обычных групп.
                            Этот параметр должен быть числом от Min_Data = 1 до Max_Data = 16. */
  uint32_t SamplingTime; /*Значение времени выборки*/

} ADC_Structure;

/*var*/

/*func*/
Rezult_t ADC_Init(ADC_TypeDef* instance);
Rezult_t ADC_SetStructure(ADC_Structure* adc);
Rezult_t ADC_MspInit(ADC_Structure* adc);
Rezult_t ADC_SetReg(ADC_Structure* adc);
Rezult_t ADC_ConfigChannel(ADC_Structure* adc);
Rezult_t ADC_Start_IT(ADC_Structure* adc);

#endif