
#include "header.h"

void predict_unit5(union Entry* data, double* result) {
  unsigned int tmp;
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0008086984144812634;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.803731059838205808) ) ) {
            result[0] += -0.0007408696243932123;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.932576353658176371) ) ) {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7593447680904524821) ) ) {
                  if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9808239647505231362) ) ) {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01030150000000000163) ) ) {
                      result[0] += -0.001054446973321712;
                    } else {
                      result[0] += 0.0020934341242286785;
                    }
                  } else {
                    result[0] += -0.0003277374206865785;
                  }
                } else {
                  result[0] += -0.0008583044297035716;
                }
              } else {
                result[0] += -1.714794724994048e-05;
              }
            } else {
              result[0] += -0.0008583044297035716;
            }
          }
        } else {
          result[0] += -0.0006737090566058875;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8650000000000001021) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4550000000000000711) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            result[0] += -0.0004436214596697565;
          } else {
            result[0] += -0.0016900509476632472;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2070606536698188782) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005458500000000000678) ) ) {
                result[0] += 0.00015198238919176142;
              } else {
                result[0] += 0.0015341593991350128;
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5180644051256282356) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4891798216080402439) ) ) {
                    result[0] += -0.0008788376468341574;
                  } else {
                    result[0] += 0.0015909075272863209;
                  }
                } else {
                  result[0] += -0.0008108619501828408;
                }
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2323027026914575854) ) ) {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01009750000000000057) ) ) {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5458973873869347182) ) ) {
                      result[0] += -0.0005184061964766733;
                    } else {
                      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5525538534170856275) ) ) {
                        result[0] += 0.0013528668611219766;
                      } else {
                        result[0] += 0.00011446147260345739;
                      }
                    }
                  } else {
                    result[0] += 0.0014975237665814278;
                  }
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6247722585678393559) ) ) {
                    result[0] += -0.0008164709946141737;
                  } else {
                    result[0] += 3.655314955573217e-05;
                  }
                }
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9993516786272610419) ) ) {
              result[0] += 0.0014027453392783853;
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7974125133417085953) ) ) {
                result[0] += -0.002439519814402409;
              } else {
                result[0] += 0.0035456340467482283;
              }
            }
          }
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03566000000000000419) ) ) {
            result[0] += 0.000493902474867803;
          } else {
            result[0] += 0.0008262385728062619;
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
            result[0] += -0.0003533325902454812;
          } else {
            result[0] += 0.00030566689252845876;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005358500000000001283) ) ) {
        result[0] += 0.0004660200671497897;
      } else {
        result[0] += 0.0004660200671497897;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
        result[0] += 0.0005381161588934365;
      } else {
        result[0] += 0.0005381161588934365;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.000774552923459343;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.932576353658176371) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                result[0] += -0.0006876681309902086;
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9808239647505231362) ) ) {
                  result[0] += -0.0006087583634053422;
                } else {
                  result[0] += 0.0025392165195898117;
                }
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += -0.0008220644350730432;
              } else {
                result[0] += -0.00041824555402707024;
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              result[0] += -0.0008220644350730432;
            } else {
              result[0] += -0.0009855017733953874;
            }
          }
        } else {
          result[0] += -0.000645263190839626;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7550000000000001155) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3450000000000000289) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7240686518592965859) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                  result[0] += 0.0013329551053394828;
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.468148307738693481) ) ) {
                    result[0] += 0.0002172665467201026;
                  } else {
                    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                      if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1296381427427941713) ) ) {
                        result[0] += -0.0005820882037168586;
                      } else {
                        result[0] += -0.0024776158722766293;
                      }
                    } else {
                      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.009795894273113748066) ) ) {
                        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5673593061306533292) ) ) {
                          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5458973873869347182) ) ) {
                            result[0] += 0.00023627262813741826;
                          } else {
                            result[0] += 0.0030094976540941615;
                          }
                        } else {
                          result[0] += -0.0016264762832877565;
                        }
                      } else {
                        result[0] += -0.0004844584495322411;
                      }
                    }
                  }
                }
              } else {
                result[0] += -0.0047388703092363345;
              }
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9186477097784532253) ) ) {
                result[0] += 0.0006919125543896362;
              } else {
                result[0] += 0.008725867287750454;
              }
            }
          } else {
            result[0] += -0.0007429491816375997;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03566000000000000419) ) ) {
            result[0] += 7.674404857323544e-05;
          } else {
            result[0] += 0.0008851460779314014;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9650000000000000799) ) ) {
            result[0] += 0.0010473307974900924;
          } else {
            result[0] += 0.0001729500360257749;
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            result[0] += 0.0008071238735499638;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08693186820944626136) ) ) {
              result[0] += 0.0004546836106724497;
            } else {
              result[0] += 0.00020233919617843526;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005358500000000001283) ) ) {
        result[0] += 0.0004463434068102178;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.07127303416489440269) ) ) {
          result[0] += 0.000593055557466059;
        } else {
          result[0] += 0.00029728377382762125;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
        result[0] += 0.0005153954015094469;
      } else {
        result[0] += 0.0005153954015094469;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0007418491498146925;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.932576353658176371) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                  result[0] += -0.000680552796478807;
                } else {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.071894537606111239) ) ) {
                    result[0] += -0.0028368487613945155;
                  } else {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5525538534170856275) ) ) {
                      result[0] += 0.0014956510546607685;
                    } else {
                      result[0] += -0.0005235903377351915;
                    }
                  }
                }
              } else {
                result[0] += 0.00025068292705460616;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += -0.0007873545935739327;
              } else {
                result[0] += -0.00040058606619544136;
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              result[0] += -0.0007873545935739327;
            } else {
              result[0] += -0.000943891153969178;
            }
          }
        } else {
          result[0] += -0.0006180183884571172;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4550000000000000711) ) ) {
          result[0] += -0.0004206750371331264;
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7210440605025126848) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.679632490452261373) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005566500000000001135) ) ) {
                result[0] += -3.68029104817928e-05;
              } else {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
                    result[0] += 0.000724125138625371;
                  } else {
                    result[0] += 0.0033468237100413613;
                  }
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5180644051256282356) ) ) {
                      result[0] += -0.0003400845933119796;
                    } else {
                      result[0] += 0.0005565258585637227;
                    }
                  } else {
                    result[0] += 0.0014386810303413662;
                  }
                }
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6800105846231156992) ) ) {
                result[0] += 0.006355756345164816;
              } else {
                result[0] += 0.0008403227125876859;
              }
            }
          } else {
            result[0] += -0.00027572027011094004;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03566000000000000419) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9550000000000000711) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9750000000000000888) ) ) {
              result[0] += 0.0009587232233736063;
            } else {
              result[0] += 0.0001750854221800971;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.008191000000000002099) ) ) {
              result[0] += 0.0004628790831505177;
            } else {
              result[0] += 0.00027251390102654753;
            }
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08390973343508316418) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5131783528140704265) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5012509875628141653) ) ) {
                result[0] += 0.0008447011586216972;
              } else {
                result[0] += -8.058193084216135e-05;
              }
            } else {
              result[0] += 0.0009476819477491071;
            }
          } else {
            result[0] += 0.0004717726045569633;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005358500000000001283) ) ) {
        result[0] += 0.00042749754966864127;
      } else {
        result[0] += 0.00042632181922619964;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
        result[0] += 0.000493633977547377;
      } else {
        result[0] += 0.000493633977547377;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0007105262202391904;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.932576353658176371) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                  result[0] += -0.0006518179690252183;
                } else {
                  result[0] += -0.0005841864990047645;
                }
              } else {
                result[0] += 0.00024009839828366452;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += -0.0007541102978951889;
              } else {
                result[0] += -0.0003836722109413084;
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              result[0] += -0.0007541102978951889;
            } else {
              result[0] += -0.000904037450355578;
            }
          }
        } else {
          result[0] += -0.0005919239372296091;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8650000000000001021) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.5350000000000001421) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02972700000000000342) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8274453021105528938) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
                result[0] += -0.0004557220894779078;
              } else {
                result[0] += 0.001859192328966075;
              }
            } else {
              result[0] += -0.0011211079738102025;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
              result[0] += 0.00019721781168118745;
            } else {
              result[0] += -0.004367847536022946;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2070606536698188782) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005458500000000000678) ) ) {
                result[0] += 0.00020918293830524685;
              } else {
                if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9850000000000000977) ) ) {
                  result[0] += 0.0016059870597215599;
                } else {
                  result[0] += -0.00023955653432602603;
                }
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5145936098743719711) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4891798216080402439) ) ) {
                    result[0] += -0.0008562085240294584;
                  } else {
                    result[0] += 0.0014605710045358653;
                  }
                } else {
                  result[0] += -0.0009003306555294368;
                }
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.05463331189772155372) ) ) {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01009750000000000057) ) ) {
                    result[0] += 0.00011815853633006085;
                  } else {
                    result[0] += 0.0020818328577538597;
                  }
                } else {
                  result[0] += 1.758312677331355e-05;
                }
              }
            }
          } else {
            result[0] += 0.0010794896624002075;
          }
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
              result[0] += 0.0007325649092755426;
            } else {
              result[0] += 0.0007262896341938414;
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9550000000000000711) ) ) {
              result[0] += 0.00035095303032443885;
            } else {
              result[0] += 0.00043293002606637333;
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5673593061306533292) ) ) {
            result[0] += -0.00016173466257889092;
          } else {
            result[0] += 0.00031916980702342764;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      result[0] += 0.0005500146160712131;
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
        result[0] += 0.0004727913812882113;
      } else {
        result[0] += 0.0004727913812882113;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.000680525831664695;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.932576353658176371) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4389499174623116007) ) ) {
                  result[0] += 0.002879365161688737;
                } else {
                  result[0] += -0.0006464087671518478;
                }
              } else {
                result[0] += 0.00022996077768720142;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += -0.0007222696686257043;
              } else {
                result[0] += -0.00036747250558828124;
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              result[0] += -0.0007222696686257043;
            } else {
              result[0] += -0.0008658664806939188;
            }
          }
        } else {
          result[0] += -0.0005669312661393629;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8650000000000001021) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.5350000000000001421) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02972700000000000342) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.316725863161028132) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.114862829452247572) ) ) {
                    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.045304313006248043) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7683067979899498301) ) ) {
                        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7640286906783920751) ) ) {
                          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.7760221401809592745) ) ) {
                            result[0] += -0.0003338529351092105;
                          } else {
                            result[0] += -0.0012184733583319046;
                          }
                        } else {
                          result[0] += 0.003197010879536553;
                        }
                      } else {
                        result[0] += -0.0015296237978183783;
                      }
                    } else {
                      result[0] += 0.001595329970384265;
                    }
                  } else {
                    result[0] += -0.0013422854241601468;
                  }
                } else {
                  result[0] += 0.0010330538029310419;
                }
              } else {
                result[0] += 0.00022492078061954007;
              }
            } else {
              result[0] += -0.0046549505890184075;
            }
          } else {
            result[0] += -0.000910523427261958;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2070606536698188782) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005458500000000000678) ) ) {
                result[0] += 0.00020035065421275972;
              } else {
                if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9850000000000000977) ) ) {
                  result[0] += 0.001538177829794704;
                } else {
                  result[0] += -0.00022944179272940793;
                }
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5145936098743719711) ) ) {
                result[0] += -0.0004175557180301259;
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2323027026914575854) ) ) {
                  result[0] += 0.000441425771568664;
                } else {
                  result[0] += -3.6753207606846785e-05;
                }
              }
            }
          } else {
            result[0] += 0.0010339106135042273;
          }
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03566000000000000419) ) ) {
            result[0] += 0.0004035079330945534;
          } else {
            result[0] += 0.0006849836116565697;
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5673593061306533292) ) ) {
            result[0] += -0.00015490577634623792;
          } else {
            result[0] += 0.000305693572143981;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      result[0] += 0.0005267914728095433;
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
        result[0] += 0.00045282881727678966;
      } else {
        result[0] += 0.00045282881727678966;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0006517921427403795;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.932576353658176371) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002803500000000000436) ) ) {
                result[0] += -0.0005970032339264915;
              } else {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.071894537606111239) ) ) {
                  result[0] += -0.002542638262991738;
                } else {
                  result[0] += 1.267478065638523e-05;
                }
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += -0.0006917734390748106;
              } else {
                result[0] += -0.000351956796745924;
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              result[0] += -0.0006917734390748106;
            } else {
              result[0] += -0.0008293071952875284;
            }
          }
        } else {
          result[0] += -0.000542993854971784;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8650000000000001021) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3450000000000000289) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.468148307738693481) ) ) {
            result[0] += 0.000258705734823449;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.394135022639764854) ) ) {
                  result[0] += -0.0004193293062601982;
                } else {
                  result[0] += 0.0014094789375655432;
                }
              } else {
                result[0] += -0.003986879962877868;
              }
            } else {
              result[0] += -0.001028842794400696;
            }
          }
        } else {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004848500000000001246) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
              result[0] += -0.00010546521807446804;
            } else {
              result[0] += 0.0003620943658133521;
            }
          } else {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2070606536698188782) ) ) {
              result[0] += 0.0011579095598441788;
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5180644051256282356) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07794150000000001077) ) ) {
                  result[0] += -0.0008171581854656241;
                } else {
                  result[0] += 0.00042098155584852114;
                }
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.05463331189772155372) ) ) {
                  if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01009750000000000057) ) ) {
                    result[0] += 0.00015004565205965797;
                  } else {
                    result[0] += 0.0017796820388381674;
                  }
                } else {
                  result[0] += 0.00020349778868864138;
                }
              }
            }
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0325310000000000113) ) ) {
          if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2834761482106662456) ) ) {
            result[0] += 0.0005079637379662961;
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9550000000000000711) ) ) {
              result[0] += 0.0001371525514732218;
            } else {
              result[0] += 0.00034091052517413474;
            }
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08693186820944626136) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5190499213819096402) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5012509875628141653) ) ) {
                result[0] += 0.0006571623199214528;
              } else {
                result[0] += 2.9727720808595817e-05;
              }
            } else {
              result[0] += 0.0006685829072727742;
            }
          } else {
            result[0] += 0.0003819378633393249;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      result[0] += 0.0005045488750955607;
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
        result[0] += 0.0004337091281097094;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
          result[0] += 0.0004337091281097094;
        } else {
          result[0] += 0.0004337091281097094;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.000624271669892197;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.932576353658176371) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7593447680904524821) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6193272217839197458) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2416736107842603343) ) ) {
                  result[0] += -0.0007704227246961351;
                } else {
                  result[0] += 0.0011061414238682575;
                }
              } else {
                result[0] += -0.0005923004789421044;
              }
            } else {
              result[0] += -0.0006625648449559715;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              result[0] += -0.0006625648449559715;
            } else {
              result[0] += -0.0007942915443550753;
            }
          }
        } else {
          result[0] += -0.0004862472717099087;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6950000000000000622) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.29500000000000004) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003653500000000000497) ) ) {
              result[0] += -0.0006115004645882244;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                result[0] += -0.00010035761961168862;
              } else {
                result[0] += -0.0026153929771334686;
              }
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
              result[0] += 0.0008517648283702546;
            } else {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00196950000000000033) ) ) {
                if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6550000000000001377) ) ) {
                  result[0] += -0.0008057993078309429;
                } else {
                  result[0] += -0.00010971001608887745;
                }
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.7760221401809592745) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6722423356281408413) ) ) {
                    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.482877277201360311) ) ) {
                      result[0] += 0.0002880651240358137;
                    } else {
                      result[0] += -0.0013413727029466293;
                    }
                  } else {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6828811456281408399) ) ) {
                      result[0] += 0.004068072728335618;
                    } else {
                      result[0] += 0.0004524013661232659;
                    }
                  }
                } else {
                  result[0] += -0.00038168191763441727;
                }
              }
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04871150000000001173) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.03588532983514210878) ) ) {
              result[0] += 0.00041984892781243984;
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5705607401507538645) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02804500000000000395) ) ) {
                  result[0] += -0.0005319306693720195;
                } else {
                  result[0] += 0.0006365289629070107;
                }
              } else {
                result[0] += 0.0002041652619725615;
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9993516786272610419) ) ) {
              result[0] += 0.0006253913167796538;
            } else {
              result[0] += -0.00037988506608681544;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08390973343508316418) ) ) {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
          result[0] += 0.0006130531808463361;
        } else {
          result[0] += 0.00048324542157544246;
        }
      } else {
        result[0] += 0.0002202299539040965;
      }
    } else {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
          result[0] += 0.00041539672527225144;
        } else {
          result[0] += 0.00041539672527225144;
        }
      } else {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8011796369346734226) ) ) {
          result[0] += 0.00041539672527225144;
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
            result[0] += -0.0004290579650499744;
          } else {
            result[0] += 0.00041539672527225144;
          }
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.0005979131877710019;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.932576353658176371) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7593447680904524821) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6193272217839197458) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2416736107842603343) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5750608109547740154) ) ) {
                    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.071894537606111239) ) ) {
                      result[0] += -0.0017420640784720867;
                    } else {
                      result[0] += 0.0002139823286984928;
                    }
                  } else {
                    result[0] += -0.0011283134448200932;
                  }
                } else {
                  result[0] += 0.001059437063650246;
                }
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.4725173572200235816) ) ) {
                  result[0] += -0.001161801872302836;
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6990533298743719648) ) ) {
                    result[0] += -0.0001636850268896177;
                  } else {
                    result[0] += -0.0005013071422453351;
                  }
                }
              }
            } else {
              result[0] += -0.000634589518728337;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              result[0] += -0.000634589518728337;
            } else {
              result[0] += -0.0007607543513658193;
            }
          }
        } else {
          result[0] += -0.00046571656266770797;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6950000000000000622) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1450000000000000455) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
              result[0] += -0.0007630522078042055;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                result[0] += -0.00016274579699381779;
              } else {
                result[0] += -0.0022769950939044332;
              }
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
                result[0] += 0.00028450785523419323;
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5068267582412061545) ) ) {
                  result[0] += -0.00238707245500108;
                } else {
                  result[0] += -9.543422057560526e-05;
                }
              }
            } else {
              result[0] += 0.0012679471511816596;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04871150000000001173) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2834761482106662456) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4230630641206030718) ) ) {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.212199032544347022) ) ) {
                  result[0] += 0.0011513107449008563;
                } else {
                  result[0] += 0.00024438573204967724;
                }
              } else {
                result[0] += 0.0007243281072756831;
              }
            } else {
              result[0] += 0.0001812117712659783;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9993516786272610419) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1932010000000000394) ) ) {
                result[0] += 0.0005554246639160643;
              } else {
                result[0] += 0.0007230254004018293;
              }
            } else {
              result[0] += -0.00036384526449805146;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08390973343508316418) ) ) {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
          result[0] += 0.0005871683744615273;
        } else {
          result[0] += 0.00046284145897540274;
        }
      } else {
        result[0] += 0.00021093123415995646;
      }
    } else {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
          result[0] += 0.00039785752289553264;
        } else {
          result[0] += 0.00039785752289553264;
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
          result[0] += 0.00039785752289553264;
        } else {
          result[0] += 0.00039785752289553264;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.0005726676339040288;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.803731059838205808) ) ) {
            result[0] += -0.0006261881656671505;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7847910031909549611) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.966590843157139501) ) ) {
                  result[0] += -0.0006077953883994897;
                } else {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                    result[0] += -0.00018024421051931623;
                  } else {
                    result[0] += -0.0011123625547038163;
                  }
                }
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -0.0006077953883994897;
                } else {
                  result[0] += 0.0005938152449118621;
                }
              }
            } else {
              result[0] += -0.0007286331917229989;
            }
          }
        } else {
          result[0] += -0.0004460527171295289;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5950000000000000844) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1450000000000000455) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
              result[0] += -0.0007308340262865038;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                result[0] += -0.0001558742178604861;
              } else {
                result[0] += -0.0021808540428727673;
              }
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
              result[0] += -8.67038183640804e-05;
            } else {
              result[0] += 0.0012144109041807149;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02361250000000000501) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.212199032544347022) ) ) {
              result[0] += 0.0012989029683332881;
            } else {
              result[0] += 0.00017832468528288152;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9993516786272610419) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.2059025000000000161) ) ) {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1890520899528410625) ) ) {
                  result[0] += 0.0007417415925543134;
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5180644051256282356) ) ) {
                    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06607900000000001273) ) ) {
                      result[0] += -0.0007275585177332663;
                    } else {
                      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5068267582412061545) ) ) {
                        result[0] += 0.0010260499634201301;
                      } else {
                        result[0] += -0.00029386249255165727;
                      }
                    }
                  } else {
                    if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.05463331189772155372) ) ) {
                      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.0841877145549009831) ) ) {
                        result[0] += 3.53674374499527e-05;
                      } else {
                        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.01778816268138619719) ) ) {
                          result[0] += 0.0011897006769648925;
                        } else {
                          result[0] += 0.0007451851967795491;
                        }
                      }
                    } else {
                      result[0] += 0.00041471481369595214;
                    }
                  }
                }
              } else {
                result[0] += 0.0006974886101783859;
              }
            } else {
              result[0] += -0.0008667049280845629;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08390973343508316418) ) ) {
        result[0] += 0.0004432990082929036;
      } else {
        result[0] += 0.0002020251321653449;
      }
    } else {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
          result[0] += 0.00038105887431063597;
        } else {
          result[0] += 0.00038105887431063597;
        }
      } else {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8011796369346734226) ) ) {
          result[0] += 0.00038105887431063597;
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
            result[0] += -0.0004277405958077612;
          } else {
            result[0] += 0.00038105887431063597;
          }
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.0005484880173722501;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.803731059838205808) ) ) {
            result[0] += -0.0005997487637764771;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7847910031909549611) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.966590843157139501) ) ) {
                  result[0] += -0.0005821325806010207;
                } else {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                    result[0] += -0.00017263379981263984;
                  } else {
                    result[0] += -0.0010653955210796402;
                  }
                }
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -0.0005821325806010207;
                } else {
                  result[0] += 0.0005687427175633036;
                }
              }
            } else {
              result[0] += -0.0006978682765695425;
            }
          }
        } else {
          result[0] += -0.00042721913371287384;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6650000000000001465) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1450000000000000455) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
              result[0] += -0.0006999761857909377;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.03500000000000001027) ) ) {
                  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
                    result[0] += -5.299948760471996e-05;
                  } else {
                    result[0] += 0.0016583636705965984;
                  }
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
                    result[0] += 0.0003977392352789418;
                  } else {
                    result[0] += -0.000616407566117044;
                  }
                }
              } else {
                result[0] += -0.002088772333786201;
              }
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07584250000000002101) ) ) {
              result[0] += -7.797064891476807e-05;
            } else {
              result[0] += 0.0006762448396823334;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01196600000000000268) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.2635054734422110356) ) ) {
              result[0] += 0.0010449329869270713;
            } else {
              result[0] += 0.00012098004519924273;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08390973343508316418) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5131783528140704265) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5012509875628141653) ) ) {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07584250000000002101) ) ) {
                    if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.0491948752242571466) ) ) {
                      result[0] += 0.0006957694021550294;
                    } else {
                      result[0] += -0.0011035912038222964;
                    }
                  } else {
                    result[0] += 0.0007159679901271431;
                  }
                } else {
                  result[0] += -0.00018121845493973503;
                }
              } else {
                result[0] += 0.0007831780729841584;
              }
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
                result[0] += 9.769692248547872e-05;
              } else {
                result[0] += 0.0007343012611340545;
              }
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08390973343508316418) ) ) {
        result[0] += 0.0004245816941042763;
      } else {
        result[0] += 0.00019349507050944286;
      }
    } else {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
          result[0] += 0.0003649695112815984;
        } else {
          result[0] += 0.0003649695112815984;
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
            result[0] += 0.0003649695112815984;
          } else {
            result[0] += 0.0003649695112815984;
          }
        } else {
          result[0] += 0.0003649695112815984;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.0005253293313436292;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.803731059838205808) ) ) {
            result[0] += -0.0005744257067972279;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7847910031909549611) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.966590843157139501) ) ) {
                  result[0] += -0.0005575533277565228;
                } else {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                    result[0] += -0.00016534472176323676;
                  } else {
                    result[0] += -0.0010204115659383976;
                  }
                }
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -0.0005575533277565228;
                } else {
                  result[0] += 0.000544728821890221;
                }
              }
            } else {
              result[0] += -0.0006684023414998251;
            }
          }
        } else {
          result[0] += -0.000409180756447175;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5950000000000000844) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7240686518592965859) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03034700000000000245) ) ) {
                  if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2050000000000000433) ) ) {
                    result[0] += -0.0004123727649238212;
                  } else {
                    result[0] += -2.1596179232769744e-05;
                  }
                } else {
                  result[0] += 0.0005035141779671754;
                }
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9186477097784532253) ) ) {
                  result[0] += 0.0005145005959904622;
                } else {
                  result[0] += 0.008284158206864494;
                }
              }
            } else {
              result[0] += -0.0027977523806751903;
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.735388073517588059) ) ) {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8440161800932387548) ) ) {
                result[0] += -0.00031407072916000235;
              } else {
                result[0] += -0.0025025157431845064;
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.394135022639764854) ) ) {
                  result[0] += -0.00041428847710645185;
                } else {
                  result[0] += 0.0011799729131143563;
                }
              } else {
                result[0] += -0.0007466623386467163;
              }
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01421250000000000117) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.212199032544347022) ) ) {
              result[0] += 0.001101464330188202;
            } else {
              result[0] += 0.00011630591946563387;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.04446937286580055632) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5499504253266332965) ) ) {
                result[0] += 0.0005839109836664504;
              } else {
                result[0] += 0.0009943663899927128;
              }
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.3075945000000000484) ) ) {
                result[0] += 0.00020205303248576297;
              } else {
                result[0] += 0.0009454855225176424;
              }
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.0005257321649912756;
      } else {
        result[0] += 0.0003436655331511432;
      }
    } else {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
          result[0] += 0.00034955948580413416;
        } else {
          result[0] += 0.00034955948580413416;
        }
      } else {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8011796369346734226) ) ) {
          result[0] += 0.00034955948580413416;
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
            result[0] += -0.0004250902264429371;
          } else {
            result[0] += 0.00034955948580413416;
          }
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.0005031484692994626;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.803731059838205808) ) ) {
            result[0] += -0.0005501718595496278;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7847910031909549611) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.966590843157139501) ) ) {
                  result[0] += -0.0005340118791692099;
                } else {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                    result[0] += -0.00015836340881468847;
                  } else {
                    result[0] += -0.0009773269582039274;
                  }
                }
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -0.0005340118791692099;
                } else {
                  result[0] += 0.0005217288595258027;
                }
              }
            } else {
              result[0] += -0.0006401805399703235;
            }
          }
        } else {
          result[0] += -0.0003919040095222144;
        }
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6750000000000001554) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7240686518592965859) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02170000000000000401) ) ) {
                  result[0] += -0.0002471079329394708;
                } else {
                  result[0] += 0.0004130438008188982;
                }
              } else {
                result[0] += -0.002622207657056507;
              }
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9186477097784532253) ) ) {
                result[0] += 0.0005190330329560143;
              } else {
                result[0] += 0.007828235969805511;
              }
            }
          } else {
            if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9033411549107539518) ) ) {
              result[0] += -0.0010781609795511887;
            } else {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9186477097784532253) ) ) {
                result[0] += 0.002783971369595503;
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9310018456912946272) ) ) {
                  result[0] += -0.001995092878812404;
                } else {
                  if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9567162861906464144) ) ) {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7536081807788946874) ) ) {
                      result[0] += -0.0016968611118712569;
                    } else {
                      result[0] += 0.003155280418489486;
                    }
                  } else {
                    if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.992027305872230758) ) ) {
                      result[0] += -0.001563841981114048;
                    } else {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8490362337185931585) ) ) {
                        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
                          result[0] += -0.00040928642996150084;
                        } else {
                          result[0] += 0.0006677045357827777;
                        }
                      } else {
                        result[0] += -0.0007285410269341758;
                      }
                    }
                  }
                }
              }
            }
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8650000000000001021) ) ) {
            result[0] += 0.0002410743966011349;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9750000000000000888) ) ) {
              result[0] += 0.0006232886438672607;
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08494950000000001111) ) ) {
                result[0] += 0.00018034612697808924;
              } else {
                result[0] += 0.00047021619715159016;
              }
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01291500000000000113) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
          result[0] += 0.0002686352398885442;
        } else {
          result[0] += 0.00042682899134541084;
        }
      } else {
        result[0] += 0.00037938523607526826;
      }
    } else {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
          result[0] += 0.0003348001143618027;
        } else {
          result[0] += 0.0003348001143618027;
        }
      } else {
        result[0] += 0.0003348001143618027;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.00048190414479787694;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.803731059838205808) ) ) {
            result[0] += -0.0005269420770319816;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7847910031909549611) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.966590843157139501) ) ) {
                  result[0] += -0.000511464415863662;
                } else {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                    result[0] += -0.00015167686627045557;
                  } else {
                    result[0] += -0.0009360615021584388;
                  }
                }
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -0.000511464415863662;
                } else {
                  result[0] += 0.0004997000193923121;
                }
              }
            } else {
              result[0] += -0.0006131503412107695;
            }
          }
        } else {
          result[0] += -0.0003753567347916474;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6650000000000001465) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.29500000000000004) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003653500000000000497) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8274453021105528938) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
                  result[0] += -0.0005176773244060629;
                } else {
                  result[0] += 0.0007522742436564166;
                }
              } else {
                result[0] += -0.0008307063920941945;
              }
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                result[0] += -9.616053825302004e-05;
              } else {
                result[0] += -0.0019997015525454113;
              }
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
              result[0] += 0.000762735594281044;
            } else {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00196950000000000033) ) ) {
                result[0] += -0.0004254840548690367;
              } else {
                result[0] += 0.00012436736139591752;
              }
            }
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.03945373639888280493) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01421250000000000117) ) ) {
              result[0] += 0.00028662450440545607;
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5131783528140704265) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5012509875628141653) ) ) {
                  if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.0491948752242571466) ) ) {
                    if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.05751864358971629093) ) ) {
                      result[0] += 0.0006154207693956705;
                    } else {
                      result[0] += 0.0015638039692319242;
                    }
                  } else {
                    result[0] += -0.000992324849821108;
                  }
                } else {
                  result[0] += -0.00021557496574232702;
                }
              } else {
                result[0] += 0.0007205705760495038;
              }
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5705607401507538645) ) ) {
              result[0] += -0.00032334126659205745;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.316725863161028132) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
                  result[0] += 0.00018063988143311176;
                } else {
                  result[0] += 0.0014292142699648509;
                }
              } else {
                result[0] += -0.0007247078011514391;
              }
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.000490348295728631;
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007599500000000001219) ) ) {
          result[0] += 0.00025729271465598457;
        } else {
          result[0] += 0.00031486861142479105;
        }
      }
    } else {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
          result[0] += 0.0003206639245358186;
        } else {
          result[0] += 0.0003206639245358186;
        }
      } else {
        result[0] += 0.0003206639245358186;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.00046155681462513635;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.803731059838205808) ) ) {
            result[0] += -0.0005046931203898335;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7847910031909549611) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.966590843157139501) ) ) {
                  result[0] += -0.0004898689690231896;
                } else {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                    result[0] += -0.00014527264810614408;
                  } else {
                    result[0] += -0.0008965383881698721;
                  }
                }
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -0.0004898689690231896;
                } else {
                  result[0] += 0.00047860129801450613;
                }
              }
            } else {
              result[0] += -0.0005872614324457767;
            }
          }
        } else {
          result[0] += -0.00035950813191529995;
        }
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6750000000000001554) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7240686518592965859) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03034700000000000245) ) ) {
                  result[0] += -0.0002131783139708143;
                } else {
                  result[0] += 0.00044816481472337766;
                }
              } else {
                result[0] += -0.002507430608968989;
              }
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9186477097784532253) ) ) {
                result[0] += 0.0004965225329301834;
              } else {
                result[0] += 0.007492454990414556;
              }
            }
          } else {
            if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9033411549107539518) ) ) {
              result[0] += -0.001010993753194038;
            } else {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9186477097784532253) ) ) {
                result[0] += 0.0026882821465336712;
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9310018456912946272) ) ) {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05256900000000001155) ) ) {
                    result[0] += -0.002332444755260122;
                  } else {
                    result[0] += -0.00035610771556817295;
                  }
                } else {
                  if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9567162861906464144) ) ) {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7536081807788946874) ) ) {
                      result[0] += -0.001603357154228273;
                    } else {
                      result[0] += 0.003003327749849359;
                    }
                  } else {
                    if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.992027305872230758) ) ) {
                      result[0] += -0.0014902779712634487;
                    } else {
                      result[0] += -0.00028123816679497394;
                    }
                  }
                }
              }
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01314200000000000264) ) ) {
            result[0] += 0.00010174814978240875;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1324529432504036319) ) ) {
              result[0] += 0.0005579085940365154;
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
                result[0] += -0.0016243830784465959;
              } else {
                result[0] += 0.0002313039376249939;
              }
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.0004696444300729105;
      } else {
        result[0] += 0.0002998416968991125;
      }
    } else {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
          result[0] += 0.00030712460386914765;
        } else {
          result[0] += 0.00030712460386914765;
        }
      } else {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8011796369346734226) ) ) {
          result[0] += 0.00030712460386914765;
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
            result[0] += -0.0004348172480420831;
          } else {
            result[0] += 0.00030712460386914765;
          }
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.0004420686051917124;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.803731059838205808) ) ) {
            result[0] += -0.0004833835764331411;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7847910031909549611) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.966590843157139501) ) ) {
                  result[0] += -0.00046918534187099836;
                } else {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                    result[0] += -0.00013913883380304475;
                  } else {
                    result[0] += -0.0008586840497219628;
                  }
                }
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -0.00046918534187099836;
                } else {
                  result[0] += 0.0004583934231976422;
                }
              }
            } else {
              result[0] += -0.0005624656252449429;
            }
          }
        } else {
          result[0] += -0.0003443287010288238;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4550000000000000711) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8066186623115578769) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
                    result[0] += -0.00026754039615231975;
                  } else {
                    result[0] += -0.002105563851134993;
                  }
                } else {
                  result[0] += 0.0005119094743584213;
                }
              } else {
                result[0] += -0.0021630533235921416;
              }
            } else {
              result[0] += -0.0006124370979838045;
            }
          } else {
            if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01314200000000000264) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09250981134579591703) ) ) {
                  if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
                    result[0] += 0.0017794447642004892;
                  } else {
                    result[0] += 4.1730983627870224e-05;
                  }
                } else {
                  result[0] += 0.003077052098390378;
                }
              } else {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5131783528140704265) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
                    result[0] += 0.0008161727301028424;
                  } else {
                    result[0] += -0.0009545836415001647;
                  }
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.2059025000000000161) ) ) {
                    result[0] += 0.0011573161331771544;
                  } else {
                    result[0] += 0.0014827723003633482;
                  }
                }
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5579756078894474447) ) ) {
                result[0] += -0.0006759873360064572;
              } else {
                result[0] += 4.758266057848481e-05;
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              result[0] += 0.0005933902353978095;
            } else {
              result[0] += 0.0004707127799556091;
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9550000000000000711) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1627210000000000323) ) ) {
                result[0] += 8.618365797553296e-05;
              } else {
                result[0] += 0.0005922159249925106;
              }
            } else {
              result[0] += 0.00023980374212569517;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007599500000000001219) ) ) {
        result[0] += 0.0004394260629555712;
      } else {
        result[0] += 0.00033741176379142835;
      }
    } else {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
          result[0] += 0.0002941569508896963;
        } else {
          result[0] += 0.0002941569508896963;
        }
      } else {
        result[0] += 0.0002941569508896963;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.00042340324203611764;
    } else {
      if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.803731059838205808) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -0.00046297378055165807;
          } else {
            result[0] += 0.0006616118442634601;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8011796369346734226) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.045304313006248043) ) ) {
                  result[0] += -0.00044937503484974723;
                } else {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                    result[0] += -4.755339415789441e-05;
                  } else {
                    result[0] += -0.0008224280264808948;
                  }
                }
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                  result[0] += -0.00044937503484974723;
                } else {
                  result[0] += -0.0004130552757657298;
                }
              }
            } else {
              result[0] += 0.00011750880348511961;
            }
          } else {
            result[0] += -0.0005387167658271099;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2350000000000000144) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
              result[0] += -0.0005733361466246561;
            } else {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
                result[0] += 0.0018228378945341914;
              } else {
                result[0] += -0.00022263514815107398;
              }
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03105600000000000374) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.212199032544347022) ) ) {
                result[0] += 0.002887512135947295;
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
                  result[0] += 0.0006468257189945348;
                } else {
                  if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002009500000000000435) ) ) {
                    result[0] += -0.00032279566400091487;
                  } else {
                    if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4550000000000000711) ) ) {
                      result[0] += -0.00038398318524930094;
                    } else {
                      result[0] += 0.00016348575235973522;
                    }
                  }
                }
              }
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9993516786272610419) ) ) {
                result[0] += 0.000567005609665199;
              } else {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7974125133417085953) ) ) {
                  result[0] += -0.002081108021828238;
                } else {
                  result[0] += 0.00067224891608829;
                }
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              result[0] += 0.0005683356531302422;
            } else {
              result[0] += 0.00045083798026011775;
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9550000000000000711) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1627210000000000323) ) ) {
                result[0] += 8.2544744794867e-05;
              } else {
                result[0] += 0.000567210925368714;
              }
            } else {
              result[0] += 0.00022967856272982683;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005358500000000001283) ) ) {
        result[0] += 0.0004312609513840015;
      } else {
        result[0] += 0.0003231653028797662;
      }
    } else {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
          result[0] += 0.00028173682820145776;
        } else {
          result[0] += 0.00028173682820145776;
        }
      } else {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8011796369346734226) ) ) {
          result[0] += 0.00028173682820145776;
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
            result[0] += -0.0004288781799945269;
          } else {
            result[0] += 0.00028173682820145776;
          }
        }
      }
    }
  }
}

