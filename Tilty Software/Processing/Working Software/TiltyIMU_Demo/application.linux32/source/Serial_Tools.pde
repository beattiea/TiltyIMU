import java.nio.*;


public static byte [] float2ByteArray (float value)
{  
     return ByteBuffer.allocate(4).putFloat(value).array();
}

public static float byteArray2Float(byte[] value)
{
   if(value.length == 4)
  {
     return ByteBuffer.wrap(value).order(ByteOrder.BIG_ENDIAN).getFloat();
  }
  else return -1;
}
