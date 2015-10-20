filename = "adb.dlf"
blocksize = 1024

with open(filename, "rb") as f:
    block = f.read(blocksize)
    strArray = ["", "", "", ""]
    totalResultData = []
    rowResultData = []
    title = {"CPUR0", "CPUW0", }
    count = 0
    countHead = 0
    countInside = 0
    countRow = 0
    insideLoop = 0
    value = False

    for ch in block:
        #print hex(ord(ch))[2:]
        strArray[count] = hex(ord(ch))[2:]
        if count == 3:
            tmp = "0x"+strArray[3]+strArray[2]+strArray[1]+strArray[0]
            x = int(tmp, 16)

            count = -1
            if countHead < 8:
                #print tmp + ",",

                if countHead == 7:
                    #print " "
                    insideLoop = int(tmp, 16)
                    countInside = 0

                countHead += 1

            elif countHead == 8:
                if countInside < insideLoop:
                    if value is True:
                        #print tmp + " is " + str(x),
                        print str(x*32/1000/1024),
                        value = False
                    else:
                        value = True

                    if countInside == insideLoop-1:
                        print " "
                        countHead = 0
                        insideLoop = 0
                        countRow += 1

                    countInside += 1
            else:
                print "error!!!!"

        count += 1
