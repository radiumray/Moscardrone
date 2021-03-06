int computeIMU() {
//Read data from IMU and operate to get angles, using filters.

  // read raw accel/gyro measurements from device
  accelgyro.getMotion6(&accX, &accY, &accZ, &gyroX, &gyroY, &gyroZ);  
  
  // atan2 outputs the value of -π to π (radians) - see http://en.wikipedia.org/wiki/Atan2
  // We then convert it to 0 to 2π and then from radians to degrees
  accXangle = (atan2(accY, accZ) + PI) * RAD_TO_DEG;
  accYangle = (atan2(accX, accZ) + PI) * RAD_TO_DEG;
  accZangle = (atan2(accX, accY) + PI) * RAD_TO_DEG;   //CALCULO INVENTADO. ESTUDIAR.

  gyroXrate = (double)gyroX / 131.0;
  gyroYrate = -((double)gyroY / 131.0);
  gyroZrate = -((double)gyroZ / 131.0);

  gyroXangle += gyroXrate * ((double)(micros() - timer) / 1000000); // Calculate gyro angle without any filter
  gyroYangle += gyroYrate * ((double)(micros() - timer) / 1000000);
  gyroZangle += gyroZrate * ((double)(micros() - timer) / 1000000);
  //gyroXangle += kalmanX.getRate()*((double)(micros()-timer)/1000000); // Calculate gyro angle using the unbiased rate
  //gyroYangle += kalmanY.getRate()*((double)(micros()-timer)/1000000);
  //gyroZangle += kalmanZ.getRate()*((double)(micros()-timer)/1000000);

  compAngleX = (0.93 * (compAngleX + (gyroXrate * (double)(micros() - timer) / 1000000))) + (0.07 * accXangle); // Calculate the angle using a Complimentary filter
  compAngleY = (0.93 * (compAngleY + (gyroYrate * (double)(micros() - timer) / 1000000))) + (0.07 * accYangle);
  compAngleZ = (0.93 * (compAngleZ + (gyroZrate * (double)(micros() - timer) / 1000000))) + (0.07 * accZangle);
  //kalAngleX = kalmanX.getAngle(accXangle, gyroXrate, (double)(micros() - timer) / 1000000); // Calculate the angle using a Kalman filter
  //kalAngleY = kalmanY.getAngle(accYangle, gyroYrate, (double)(micros() - timer) / 1000000);
  //kalAngleZ = kalmanZ.getAngle(accZangle, gyroZrate, (double)(micros() - timer) / 1000000);
  
  timer = micros();
  temp = ((double)tempRaw + 12412.0) / 340.0;
  
  // display tab-separated accel/gyro x/y/z values. Must be the same number as input readings in Processing.
  #ifdef DEBUG_IMU //These values can be monitored with Graph (Processing sketch)
    /*
    Serial.print(gyroXangle); Serial.print("\t");
    Serial.print(gyroYangle); Serial.print("\t");
    Serial.print(gyroZangle); Serial.print("\t");    
    
    Serial.print(accXangle); Serial.print("\t");
    Serial.print(accYangle); Serial.print("\t");
    Serial.print(accZangle); Serial.print("\t");
    */
    Serial.print(compAngleX); Serial.print("\t");
    Serial.print(compAngleY); Serial.print("\t");
    Serial.print(compAngleZ); Serial.print("\t");
    
    //Serial.print(kalAngleY); Serial.print("\t");
    //Serial.print(kalAngleX); Serial.print("\t");
    //Serial.print(kalAngleZ); Serial.print("\t");   
    
    Serial.print(gyroXrate); Serial.print("\t"); //Print gyro rotating rate
    Serial.print(gyroYrate); Serial.print("\t"); //Print gyro rotating rate
    Serial.print(gyroZrate); Serial.print("\t"); //Print gyro rotating rate
    //Serial.print(temp);Serial.print("\t"); 
    Serial.print("\r\n");    
  #endif
  
  //would you like to return any error code?
  return(0);
}
