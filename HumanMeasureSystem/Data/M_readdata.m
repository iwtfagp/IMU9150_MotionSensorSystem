close all; clear all; clc;

[FileName,PathName,FilterIndex] = uigetfile('.txt');
FileName = [PathName FileName];

data = load(FileName);




subplot(411)
plot(data(:,1))
subplot(412)
plot(data(:,2))
subplot(413)
plot(data(:,3))
subplot(414)
plot(data(:,4))



