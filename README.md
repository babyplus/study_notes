# 调制  Modulation

*20230625*  

## 模拟载体 Analog carrier

Analog transmission is a transmission method of conveying information using a continuous signal which varies in amplitude, phase, or some other property in proportion to that information. It could be the transfer of an analog signal, using an analog modulation method such as frequency modulation (FM) or amplitude modulation (AM), or no modulation at all.

模拟传输是一种使用连续信号传输信息的传输方法，该连续信号的幅度、相位或某些其他属性与该信息成比例地变化。它可以是模拟信号的传输，使用模拟调制方法，如调频(FM)或调幅(AM)，或者根本不调制。

### 模拟数据 Analog data

#### 幅度调制 Amplitude Modulation，AM

Amplitude modulation (AM) is a modulation technique used in electronic communication, most commonly for transmitting messages with a radio wave. In amplitude modulation, the amplitude (signal strength) of the wave is varied in proportion to that of the message signal, such as an audio signal. 

调幅(AM)是一种用于电子通信的调制技术，最常用于用无线电波传输信息。在幅度调制中，波的幅度(信号强度)与消息信号(如音频信号)的幅度成比例变化。

##### 单边带调制 Single-sideband modulation，SSB

##### 双边带抑制载波传输 Double-sideband suppressed-carrier transmission，DSB-SC

#### 频率调制 Frequency Modulation，FM

In analog frequency modulation, such as radio broadcasting, of an audio signal representing voice or music, the instantaneous frequency deviation, i.e. the difference between the frequency of the carrier and its center frequency, has a functional relation to the modulating signal amplitude.

广播、信号处理和编译。幅度在模拟调频中，例如无线电广播，对表示声音或音乐的音频信号进行调频时，瞬时频率偏差，即载波频率与其中心频率之间的差值，与调制信号幅度呈函数关系。

#### 相位调制 Phase Modulation，PM

Phase modulation (PM) is a modulation pattern for conditioning communication signals for transmission. It encodes a message signal as variations in the instantaneous phase of a carrier wave.

相位调制(PM)是一种用于调制通信信号的调制方式传播。它将信息信号编码为载波瞬时相位的变化。

### 数字数据 Digital data

#### 幅度偏移调制，幅移键控，幅度键移 Amplitude-shift keying，ASK

Amplitude-shift keying (ASK) is a form of amplitude modulation that represents digital data as variations in the amplitude of a carrier wave. In an ASK system, a symbol, representing one or more bits, is sent by transmitting a fixed-amplitude carrier wave at a fixed frequency for a specific time duration. For example, if each symbol represents a single bit, then the carrier signal could be transmitted at nominal amplitude when the input value is 1, but transmitted at reduced amplitude or not at all when the input value is 0.

移幅键控(ASK)是一种幅度调制形式，它将数字数据表示为载波幅度的变化。在ASK系统中，一个表示一个或多个比特的符号是通过以固定频率在特定时间内发射固定幅度的载波来发送的。例如，如果每个符号代表一个比特，那么当输入值为1时，载波信号可以以标称幅度传输，而当输入值为0时，载波信号以降幅传输或根本不传输。

##### 开关键控 on-off keying，OOK

##### 正交幅度调制 Quadrature Amplitude Modulation，QAM

#### 频率偏移调制，频率键移 Frequency-Shift Keying，FSK

Frequency-shift keying (FSK) is a frequency modulation scheme in which digital information is encoded on a carrier signal by periodically shifting the frequency of the carrier between several discrete frequencies. The technology is used for communication systems such as telemetry, weather balloon radiosondes, caller ID, garage door openers, and low frequency radio transmission in the VLF and ELF bands. The simplest FSK is binary FSK (BFSK), in which the carrier is shifted between two discrete frequencies to transmit binary (0s and 1s) information.

频移键控(FSK)是一种频率调制方案，其中通过在几个离散频率之间周期性地移动载波的频率，将数字信息编码在载波信号上。该技术用于通信系统，如遥测、气象气球无线电探空仪、来电显示、车库开门器以及VLF和ELF频段的低频无线电传输。最简单的FSK是二进制FSK (BFSK)，其中载波在两个离散频率之间移位以传输二进制(0和1)信息。

##### 最小频移键控 Minimum-Shift Keying，MSK

##### 高斯频移键控 Gaussian Frequency Shift Keying，GFSK

#### 相位偏移调制，相位键移 Phase-Shift Keying，PSK

Phase-shift keying (PSK) is a digital modulation process which conveys data by changing (modulating) the phase of a constant frequency carrier wave. The modulation is accomplished by varying the sine and cosine inputs at a precise time. It is widely used for wireless LANs, RFID and Bluetooth communication.

相移键控(PSK)是一种通过改变(调制)恒频载波的相位来传输数据的数字调制过程。调制是通过在精确的时间改变正弦和余弦输入来完成的。广泛应用于无线局域网、RFID和蓝牙通信。

## 数字载体 Digital carrier

### 模拟数据 Analog data

#### 脉冲幅度调制 Pulse-amplitude modulation，PAM

Pulse-amplitude modulation (PAM) is a form of signal modulation where the message information is encoded in the amplitude of a series of signal pulses. It is an analog pulse modulation scheme in which the amplitudes of a train of carrier pulses are varied according to the sample value of the message signal. Demodulation is performed by detecting the amplitude level of the carrier at every single period.

脉冲幅度调制(PAM)是信号调制的一种形式，其中消息信息以一系列信号脉冲的幅度进行编码。它是一种模拟脉冲调制方案，其中一列载波脉冲的幅度根据消息信号的采样值而变化。解调是通过检测载波在每一个周期的幅度水平来完成的。

#### 脉冲宽度调制 Pulse-width modulation，PWM

Pulse-width modulation (PWM), or pulse-duration modulation (PDM), is a method of controlling the average power delivered by an electrical signal. The average value of voltage (and current) fed to the load is controlled by switching the supply between 0 and 100% at a rate faster than it takes the load to change significantly. The longer the switch is on, the higher the total power supplied to the load. Along with maximum power point tracking (MPPT), it is one of the primary methods of controlling the output of solar panels to that which can be utilized by a battery.[1] PWM is particularly suited for running inertial loads such as motors, which are not as easily affected by this discrete switching. The goal of PWM is to control a load; however, the PWM switching frequency must be selected carefully in order to smoothly do so.

脉宽调制是一种控制电信号传递的平均功率的方法。输入到负载的电压(和电流)的平均值是通过在0和100%之间切换电源来控制的，其速度比负载发生显著变化的速度要快。开关打开的时间越长，提供给负载的总功率就越高。与最大功率点跟踪(MPPT)一样，它是控制太阳能电池板输出到电池可以利用的输出的主要方法之一。PWM特别适合于运行惯性负载，如电机，不容易受到这种离散开关的影响。PWM的目标是控制负载;然而，PWM开关频率必须仔细选择，以便顺利地完成。

#### 脉冲位置调制 Pulse-position modulation，PPM 

Pulse-position modulation (PPM) is a form of signal modulation in which M message bits are encoded by transmitting a single pulse in one of 2^M possible required time shifts.This is repeated every T seconds, such that the transmitted bit rate is  bits per second. It is primarily useful for optical communications systems, which tend to have little or no multipath interference.

脉冲位置调制(PPM)是一种信号调制形式，其中通过以2^M个可能所需时移之一传输单个脉冲来编码M个消息位。这每T秒重复一次，这样传输的比特率就是每秒比特数。它主要用于光通信系统，往往很少或没有多径干扰。

### 数字数据 Digital data

#### 脉冲编码调制 Pulse-code modulation，PCM

Pulse-code modulation (PCM) is a method used to digitally represent sampled analog signals. It is the standard form of digital audio in computers, compact discs, digital telephony and other digital audio applications. In a PCM stream, the amplitude of the analog signal is sampled at uniform intervals, and each sample is quantized to the nearest value within a range of digital steps.

脉冲编码调制(PCM)是一种用于数字表示采样模拟信号的方法。它是计算机、光盘、数字电话和其他数字音频应用中数字音频的标准形式。在一个在PCM流中，模拟信号的幅度以均匀间隔采样，每个采样在数字步长范围内量化到最接近的值。