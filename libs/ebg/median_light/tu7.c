
#include "header.h"

void predict_unit7(union Entry* data, double* result) {
  unsigned int tmp;
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.00020335309106566104;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01130350000000000278) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                result[0] += -0.00021582688395343033;
              } else {
                result[0] += -0.00021582688395343033;
              }
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                result[0] += 1.0407806406972357e-06;
              } else {
                result[0] += -0.00044197811805136154;
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.555383890033505745) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7664523331407036011) ) ) {
                result[0] += -0.00018526353201169717;
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07584250000000002101) ) ) {
                  result[0] += -0.0005405713670159061;
                } else {
                  result[0] += -0.00018526353201169717;
                }
              }
            } else {
              result[0] += -0.00025882711191146636;
            }
          }
        } else {
          result[0] += -0.0001637089622486935;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7150000000000000799) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
            result[0] += 0.00023801531582682867;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5068267582412061545) ) ) {
              result[0] += -0.002217379648590818;
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007171500000000001658) ) ) {
                result[0] += -0.00021122226640792025;
              } else {
                result[0] += 0.00012401191703571507;
              }
            }
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.03945373639888280493) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03566000000000000419) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.212199032544347022) ) ) {
                result[0] += 0.0003849328875133235;
              } else {
                result[0] += 0.00015913288045552322;
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5131783528140704265) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5012509875628141653) ) ) {
                  result[0] += 0.00017824772958194838;
                } else {
                  result[0] += -0.0002153269853021636;
                }
              } else {
                result[0] += 0.0002286876540160425;
              }
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6722423356281408413) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.5508018452917812224) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
                  result[0] += -7.24933793504113e-06;
                } else {
                  result[0] += 0.0003933320333956189;
                }
              } else {
                result[0] += -0.0012366506067329008;
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7210440605025126848) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01009750000000000057) ) ) {
                  result[0] += 0.0003057793802778765;
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6800105846231156992) ) ) {
                    result[0] += 0.0007356341362982778;
                  } else {
                    result[0] += 0.00040910515096018304;
                  }
                }
              } else {
                result[0] += 9.943717457507971e-06;
              }
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.00013531321726846244;
      } else {
        result[0] += 0.00013531321726846244;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            result[0] += 0.00013531321726846244;
          } else {
            result[0] += 0.00013531321726846244;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 0.00013531321726846244;
          } else {
            result[0] += 0.00013531321726846244;
          }
        }
      } else {
        result[0] += 0.00013531321726846244;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.00019476695930019166;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01130350000000000278) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8274453021105528938) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.045304313006248043) ) ) {
                    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.803731059838205808) ) ) {
                      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.4725173572200235816) ) ) {
                        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6193272217839197458) ) ) {
                          result[0] += -0.0002063087045684812;
                        } else {
                          result[0] += -0.0006855660971096133;
                        }
                      } else {
                        if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.631355564311013695) ) ) {
                          result[0] += 0.0006515433577221801;
                        } else {
                          result[0] += -0.0001195494505223477;
                        }
                      }
                    } else {
                      result[0] += -0.00020671407404017234;
                    }
                  } else {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8011796369346734226) ) ) {
                      result[0] += 0.00019385505939729754;
                    } else {
                      result[0] += -0.00020671407404017234;
                    }
                  }
                } else {
                  result[0] += -0.00020671407404017234;
                }
              } else {
                result[0] += -0.00020671407404017234;
              }
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0002825000000000000362) ) ) {
                result[0] += 9.968359941066872e-07;
              } else {
                result[0] += -0.00042331657551391454;
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.555383890033505745) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7664523331407036011) ) ) {
                result[0] += -0.0001774411916240851;
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07584250000000002101) ) ) {
                  result[0] += -0.000517746943932316;
                } else {
                  result[0] += -0.0001774411916240851;
                }
              }
            } else {
              result[0] += -0.0002478987130575233;
            }
          }
        } else {
          result[0] += -0.00015679671560572662;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9150000000000001465) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6750000000000001554) ) ) {
            result[0] += -0.00011510216852812107;
          } else {
            result[0] += 0.0001311274985432178;
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
              result[0] += 0.0001852748800551787;
            } else {
              result[0] += 0.0002162501197913652;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08693186820944626136) ) ) {
              result[0] += 0.00017072161584024786;
            } else {
              result[0] += -5.7178662948729586e-08;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.00012959991777058874;
      } else {
        result[0] += 0.00012959991777058874;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 0.00012959991777058874;
            } else {
              result[0] += 0.00012959991777058874;
            }
          } else {
            result[0] += 0.00012959991777058874;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 0.00012959991777058874;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 0.00012959991777058874;
              } else {
                result[0] += 0.00012959991777058874;
              }
            } else {
              result[0] += 0.00012959991777058874;
            }
          }
        }
      } else {
        result[0] += 0.00012959991777058874;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.0001865433578425119;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01130350000000000278) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8274453021105528938) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.045304313006248043) ) ) {
                    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.803731059838205808) ) ) {
                      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.4725173572200235816) ) ) {
                        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6193272217839197458) ) ) {
                          result[0] += -0.00019759777859973697;
                        } else {
                          result[0] += -0.0006566195941925711;
                        }
                      } else {
                        if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.631355564311013695) ) ) {
                          result[0] += 0.0006240333892677904;
                        } else {
                          result[0] += -0.00011450174099752473;
                        }
                      }
                    } else {
                      result[0] += -0.00019798603224752104;
                    }
                  } else {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8011796369346734226) ) ) {
                      result[0] += 0.00018566996088384223;
                    } else {
                      result[0] += -0.00019798603224752104;
                    }
                  }
                } else {
                  result[0] += -0.00019798603224752104;
                }
              } else {
                result[0] += -0.00019798603224752104;
              }
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0002825000000000000362) ) ) {
                result[0] += 9.547468124320452e-07;
              } else {
                result[0] += -0.00040544297508412753;
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.555383890033505745) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7664523331407036011) ) ) {
                result[0] += -0.0001699491321529342;
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07584250000000002101) ) ) {
                  result[0] += -0.0004958862313241337;
                } else {
                  result[0] += -0.0001699491321529342;
                }
              }
            } else {
              result[0] += -0.00023743174152712795;
            }
          }
        } else {
          result[0] += -0.00015017632319600955;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9150000000000001465) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4550000000000000711) ) ) {
            result[0] += -0.00015230728853025575;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.114862829452247572) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.013855723816631915) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9993516786272610419) ) ) {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08005850000000001854) ) ) {
                    result[0] += 7.182764299938776e-05;
                  } else {
                    result[0] += 0.00044047943888968585;
                  }
                } else {
                  result[0] += -0.002345441487242372;
                }
              } else {
                result[0] += 0.0010378781471275;
              }
            } else {
              result[0] += -0.00047917255457903145;
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
              result[0] += 0.00017745206052168354;
            } else {
              result[0] += 0.00020711943968664405;
            }
          } else {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2450759342279490716) ) ) {
              result[0] += 0.00016351327550405664;
            } else {
              result[0] += 3.9948156804770805e-05;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.00012412784963067926;
      } else {
        result[0] += 0.00012412784963067926;
      }
    } else {
      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8011796369346734226) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          result[0] += 0.00012412784963067926;
        } else {
          result[0] += 0.00012412784963067926;
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
          result[0] += -0.0004244287072676346;
        } else {
          result[0] += 0.00012412784963067926;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.00017866697965708398;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01130350000000000278) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                result[0] += -0.0001896265125977765;
              } else {
                result[0] += -0.0001896265125977765;
              }
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0002825000000000000362) ) ) {
                result[0] += 9.144347527960475e-07;
              } else {
                result[0] += -0.00038832404765984667;
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.555383890033505745) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7664523331407036011) ) ) {
                result[0] += -0.00016277340822149378;
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07584250000000002101) ) ) {
                  result[0] += -0.00047494853866100013;
                } else {
                  result[0] += -0.00016277340822149378;
                }
              }
            } else {
              result[0] += -0.00022740671457831938;
            }
          }
        } else {
          result[0] += -0.0001438354621239825;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9150000000000001465) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01626400000000000415) ) ) {
            if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8274453021105528938) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
                  result[0] += -0.00024402307942847487;
                } else {
                  result[0] += 0.0011895154637843806;
                }
              } else {
                result[0] += -0.0006894061723933862;
              }
            } else {
              result[0] += 2.524804875940629e-05;
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7593447680904524821) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.145614105386054682) ) ) {
                result[0] += 0.00032043225741315427;
              } else {
                result[0] += -0.0020325787426492465;
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7936293736432161738) ) ) {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9284011333411857914) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7683067979899498301) ) ) {
                    result[0] += 0.004277135384507745;
                  } else {
                    result[0] += -0.000713726947317499;
                  }
                } else {
                  result[0] += -0.0014438913656723753;
                }
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
                  result[0] += 6.716482985640833e-05;
                } else {
                  result[0] += 0.0028454836042876522;
                }
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
              result[0] += 0.000169959542135518;
            } else {
              result[0] += 0.00019837428223159668;
            }
          } else {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2450759342279490716) ) ) {
              result[0] += 0.00015660929129843854;
            } else {
              result[0] += 3.826143477701248e-05;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.00011888682739143927;
      } else {
        result[0] += 0.00011888682739143927;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            result[0] += 0.00011888682739143927;
          } else {
            result[0] += 0.00011888682739143927;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 0.00011888682739143927;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              result[0] += 0.00011888682739143927;
            } else {
              result[0] += 0.00011888682739143927;
            }
          }
        }
      } else {
        result[0] += 0.00011888682739143927;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.00017112316401388426;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01130350000000000278) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8274453021105528938) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.045304313006248043) ) ) {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6193272217839197458) ) ) {
                      result[0] += -3.200010767835082e-05;
                    } else {
                      result[0] += -0.00018161995506349628;
                    }
                  } else {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8011796369346734226) ) ) {
                      result[0] += 0.0001858370174757766;
                    } else {
                      result[0] += -0.00018161995506349628;
                    }
                  }
                } else {
                  result[0] += -0.00018161995506349628;
                }
              } else {
                result[0] += -0.00018161995506349628;
              }
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0002825000000000000362) ) ) {
                result[0] += 8.758247801750949e-07;
              } else {
                result[0] += -0.00037192792885272583;
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.555383890033505745) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7664523331407036011) ) ) {
                result[0] += -0.00015590066326551466;
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07584250000000002101) ) ) {
                  result[0] += -0.0004548948934796553;
                } else {
                  result[0] += -0.00015590066326551466;
                }
              }
            } else {
              result[0] += -0.00021780497208456268;
            }
          }
        } else {
          result[0] += -0.0001377623298009292;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9150000000000001465) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01626400000000000415) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.2635054734422110356) ) ) {
              result[0] += 0.0019065684049488407;
            } else {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8274453021105528938) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
                    result[0] += -0.00024023375922881286;
                  } else {
                    result[0] += 0.0011392908202562514;
                  }
                } else {
                  result[0] += -0.0006602975308424881;
                }
              } else {
                result[0] += 1.6995673065826756e-05;
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
              result[0] += 0.00021417397939203664;
            } else {
              result[0] += -0.0009279389149314317;
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              result[0] += 0.0001574434589750755;
            } else {
              result[0] += 0.0001927800765037461;
            }
          } else {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1701831610694422292) ) ) {
              result[0] += 0.00014999681246303612;
            } else {
              result[0] += 3.191002042827092e-05;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.0001138670956538371;
      } else {
        result[0] += 0.0001138670956538371;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            result[0] += 0.0001138670956538371;
          } else {
            result[0] += 0.0001138670956538371;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 0.0001138670956538371;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              result[0] += 0.0001138670956538371;
            } else {
              result[0] += 0.0001138670956538371;
            }
          }
        }
      } else {
        result[0] += 0.0001138670956538371;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.00016389786919959094;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -0.00017395145660477218;
          } else {
            result[0] += -4.8771608070437635e-05;
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
            result[0] += -0.0002557056852905402;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0008885000000000000753) ) ) {
                      result[0] += -0.00017395145660477218;
                    } else {
                      result[0] += 0.007765586580725023;
                    }
                  } else {
                    result[0] += -0.00017395145660477218;
                  }
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    result[0] += 1.2199910018804618e-05;
                  } else {
                    result[0] += -0.00020860864180164318;
                  }
                }
              } else {
                result[0] += -0.00017395145660477218;
              }
            } else {
              result[0] += 8.388450277324903e-07;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9150000000000001465) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01626400000000000415) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.2635054734422110356) ) ) {
              result[0] += 0.001826067796578517;
            } else {
              result[0] += -7.463101505526735e-05;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7593447680904524821) ) ) {
                result[0] += 0.00029087661971209617;
              } else {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7936293736432161738) ) ) {
                  if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9284011333411857914) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7683067979899498301) ) ) {
                      result[0] += 0.004087499840755533;
                    } else {
                      result[0] += -0.0006926344348606587;
                    }
                  } else {
                    result[0] += -0.0013919692854248613;
                  }
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
                    result[0] += 7.256607646870466e-05;
                  } else {
                    result[0] += 0.0026231895699350776;
                  }
                }
              }
            } else {
              result[0] += -0.0008887587591140055;
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              result[0] += 0.00015079575926573281;
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
                result[0] += -8.645683128602852e-06;
              } else {
                result[0] += 0.0002564250267775196;
              }
            }
          } else {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1701831610694422292) ) ) {
              result[0] += 0.00014366353083225642;
            } else {
              result[0] += 3.0562690822412075e-05;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.00010905931091886256;
      } else {
        result[0] += 0.00010905931091886256;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            result[0] += 0.00010905931091886256;
          } else {
            result[0] += 0.00010905931091886256;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 0.00010905931091886256;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              result[0] += 0.00010905931091886256;
            } else {
              result[0] += 0.00010905931091886256;
            }
          }
        }
      } else {
        result[0] += 0.00010905931091886256;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.00015697764638098155;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -0.0001666067434293937;
          } else {
            result[0] += -4.671233544708061e-05;
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
            result[0] += -0.0002449090817298139;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                result[0] += -0.0001666067434293937;
              } else {
                result[0] += -0.0001666067434293937;
              }
            } else {
              result[0] += 8.034266630487965e-07;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9150000000000001465) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4891798216080402439) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4795216591959799435) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4751828078391960308) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4737195465326633492) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4731110269597990081) ) ) {
                      result[0] += 0.00015781239536039886;
                    } else {
                      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005566500000000001135) ) ) {
                        result[0] += 0.0006506593261758126;
                      } else {
                        result[0] += 0.0030529163633902876;
                      }
                    }
                  } else {
                    result[0] += -0.001995361032017145;
                  }
                } else {
                  result[0] += 0.002600627480033109;
                }
              } else {
                result[0] += -0.000870378197038436;
              }
            } else {
              result[0] += 0.000881366770399713;
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5068267582412061545) ) ) {
              result[0] += -0.0018044941695541565;
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007171500000000001658) ) ) {
                result[0] += -0.00014472141020918422;
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1270434093492826821) ) ) {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5180644051256282356) ) ) {
                    result[0] += -0.00026334893259426435;
                  } else {
                    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.009795894273113748066) ) ) {
                      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.0841877145549009831) ) ) {
                        result[0] += 0.00017948066435451935;
                      } else {
                        result[0] += 0.0018813430260716398;
                      }
                    } else {
                      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.002753795023577549923) ) ) {
                        result[0] += -0.0014378217307405437;
                      } else {
                        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5876205025125629255) ) ) {
                          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5485006052512563235) ) ) {
                            result[0] += 0.0010092588677972608;
                          } else {
                            result[0] += -0.0004790927203104203;
                          }
                        } else {
                          result[0] += 0.0018569614112066762;
                        }
                      }
                    }
                  }
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5531655541959800138) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5499504253266332965) ) ) {
                        result[0] += -0.0009539268246402861;
                      } else {
                        result[0] += 0.005527923188902784;
                      }
                    } else {
                      result[0] += -0.004687937165130842;
                    }
                  } else {
                    result[0] += 5.061254920380322e-05;
                  }
                }
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              result[0] += 0.00014442874388404325;
            } else {
              result[0] += 0.0001759097641854229;
            }
          } else {
            result[0] += 0.00010323369499600198;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.0001044545241959583;
      } else {
        result[0] += 0.0001044545241959583;
      }
    } else {
      result[0] += 0.0001044545241959583;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.0001503496145718897;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -0.00015957214442426416;
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05663800000000000778) ) ) {
              result[0] += -0.00014443612198588736;
            } else {
              result[0] += 0.001591738535869639;
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
            result[0] += -0.0002345683407296523;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0008885000000000000753) ) ) {
                      result[0] += -0.00015957214442426416;
                    } else {
                      result[0] += 0.007444736566475188;
                    }
                  } else {
                    result[0] += -0.00015957214442426416;
                  }
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    result[0] += 1.8719394970838697e-05;
                  } else {
                    result[0] += -0.00019276600709595883;
                  }
                }
              } else {
                result[0] += -0.00015957214442426416;
              }
            } else {
              result[0] += 7.695037600003206e-07;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9150000000000001465) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4550000000000000711) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 0.0003695281557792127;
            } else {
              result[0] += -0.00016287110552400065;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.114862829452247572) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.029588714460048626) ) ) {
                result[0] += 9.162492249946929e-05;
              } else {
                result[0] += 0.0012110353884335545;
              }
            } else {
              result[0] += -0.0004444136688692742;
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              result[0] += 0.0001383305615588498;
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
                result[0] += -1.5708036752331893e-05;
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.966590843157139501) ) ) {
                  result[0] += 0.00025414703617995983;
                } else {
                  result[0] += -0.00029980861110348074;
                }
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08693186820944626136) ) ) {
              result[0] += 0.0001332388448715898;
            } else {
              result[0] += -1.0353574663396742e-05;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.00010004416434577946;
      } else {
        result[0] += 0.00010004416434577946;
      }
    } else {
      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8011796369346734226) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 0.00010004416434577946;
            } else {
              result[0] += 0.00010004416434577946;
            }
          } else {
            result[0] += 0.00010004416434577946;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 0.00010004416434577946;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              result[0] += 0.00010004416434577946;
            } else {
              result[0] += 0.00010004416434577946;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
          result[0] += -0.00042535081259493986;
        } else {
          result[0] += 0.00010004416434577946;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 6.298736160381456e-06;
        } else {
          result[0] += 4.471030718424324e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5259885771356785922) ) ) {
            result[0] += 6.298736160381456e-06;
          } else {
            result[0] += -0.00014400143665712693;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5131783528140704265) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08693186820944626136) ) ) {
                result[0] += -0.0026900069571999478;
              } else {
                result[0] += 0.00579959337874061;
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5645244997236181783) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01911900000000000405) ) ) {
                  result[0] += 0.0004126956549486825;
                } else {
                  result[0] += 0.002904431197063015;
                }
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2030091505812350317) ) ) {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.05539262878325219158) ) ) {
                    result[0] += 0.0011493513269346105;
                  } else {
                    result[0] += -0.0008330275984190143;
                  }
                } else {
                  result[0] += -0.0001528345657086161;
                }
              }
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006028500000000000872) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8099155601256282644) ) ) {
                    result[0] += 0.0006056215748446363;
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                      result[0] += -0.0001528345657086161;
                    } else {
                      result[0] += 0.0013381877977798667;
                    }
                  }
                } else {
                  result[0] += -0.0001528345657086161;
                }
              } else {
                if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                  result[0] += 7.370131760472422e-07;
                } else {
                  result[0] += -0.0006183963181072826;
                }
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.786764172562814168) ) ) {
                result[0] += -0.00022466421450782864;
              } else {
                result[0] += -0.00020175438362203272;
              }
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9450000000000000622) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
          if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.009795894273113748066) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5458973873869347182) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5450375474120604524) ) ) {
                result[0] += 5.879769649266956e-05;
              } else {
                result[0] += -0.0023318581285036487;
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5673593061306533292) ) ) {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00112850000000000038) ) ) {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.05914074587140304151) ) ) {
                    result[0] += -0.0013651680432146683;
                  } else {
                    result[0] += 0.0014268689694556208;
                  }
                } else {
                  result[0] += 0.001805892419294413;
                }
              } else {
                result[0] += -0.0006631946620227955;
              }
            }
          } else {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.002753795023577549923) ) ) {
              result[0] += -0.0017237113586661649;
            } else {
              result[0] += -8.00974586807015e-05;
            }
          }
        } else {
          result[0] += 0.00035456047980981473;
        }
      } else {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
          result[0] += 0.00016641665231309624;
        } else {
          result[0] += 0.00010043298711881238;
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 9.582002212626776e-05;
      } else {
        result[0] += 9.582002212626776e-05;
      }
    } else {
      result[0] += 9.582002212626776e-05;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 6.0327860420648624e-06;
        } else {
          result[0] += 4.282251395352909e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5259885771356785922) ) ) {
            result[0] += 6.0327860420648624e-06;
          } else {
            result[0] += -0.00013792129642874087;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
              result[0] += -0.0019535516226916556;
            } else {
              result[0] += -0.00014638146626166085;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006028500000000000872) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8099155601256282644) ) ) {
                  result[0] += 0.0005800505514863138;
                } else {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                      result[0] += -0.00014638146626166085;
                    } else {
                      result[0] += 0.0012816857957769997;
                    }
                  } else {
                    result[0] += -0.00014638146626166085;
                  }
                }
              } else {
                if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                  result[0] += 7.058944347029791e-07;
                } else {
                  result[0] += -0.0005922859096412721;
                }
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.786764172562814168) ) ) {
                result[0] += -0.00021517826797689036;
              } else {
                result[0] += -0.00019323575372089935;
              }
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9450000000000000622) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8254037945979900703) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7847910031909549611) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7664523331407036011) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7593447680904524821) ) ) {
                    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.212199032544347022) ) ) {
                      result[0] += 0.0013241754975056622;
                    } else {
                      result[0] += 6.171481678346352e-06;
                    }
                  } else {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7605905273618090989) ) ) {
                      result[0] += -0.001974939937108005;
                    } else {
                      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7626451834170855371) ) ) {
                        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007751500000000000577) ) ) {
                          result[0] += -3.221318747680144e-05;
                        } else {
                          result[0] += 0.0044832078958833375;
                        }
                      } else {
                        result[0] += -0.0009146080140835106;
                      }
                    }
                  }
                } else {
                  if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9033411549107539518) ) ) {
                    result[0] += -0.0009109411394896867;
                  } else {
                    result[0] += 0.0016259662611247043;
                  }
                }
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.316725863161028132) ) ) {
                  result[0] += -0.0007000903125807974;
                } else {
                  result[0] += 0.0006784492055781946;
                }
              }
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                result[0] += 0.0009497243186027954;
              } else {
                result[0] += 0.004800637133930388;
              }
            }
          } else {
            result[0] += -0.0004501827969147632;
          }
        } else {
          result[0] += 0.0003395899525238905;
        }
      } else {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
          result[0] += 0.0001593900794823584;
        } else {
          result[0] += 9.619242772292205e-05;
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 9.177423491233903e-05;
      } else {
        result[0] += 9.177423491233903e-05;
      }
    } else {
      result[0] += 9.177423491233903e-05;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 5.7780650756974345e-06;
        } else {
          result[0] += 4.1014428591232136e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5259885771356785922) ) ) {
            result[0] += 5.7780650756974345e-06;
          } else {
            result[0] += -0.00013209787659186636;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01911900000000000405) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.045304313006248043) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.743670590552763966) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.4725173572200235816) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6193272217839197458) ) ) {
                      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2888738239382729889) ) ) {
                        result[0] += -0.0004537319563528824;
                      } else {
                        result[0] += 0.0010283312589394662;
                      }
                    } else {
                      result[0] += -0.0005794696149304769;
                    }
                  } else {
                    if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.5642589213209130428) ) ) {
                      result[0] += 0.0008807014002750374;
                    } else {
                      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004302500000000001636) ) ) {
                        result[0] += -0.00018823352800956646;
                      } else {
                        result[0] += 0.0009246557985539604;
                      }
                    }
                  }
                } else {
                  result[0] += -0.00014020083457930594;
                }
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7801862323115579256) ) ) {
                  result[0] += 0.0004969876660310921;
                } else {
                  result[0] += -0.00014020083457930594;
                }
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7593447680904524821) ) ) {
                result[0] += 0.0005740500407143298;
              } else {
                result[0] += -0.00013253350728430815;
              }
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006028500000000000872) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8099155601256282644) ) ) {
                  result[0] += 0.0005555592076882177;
                } else {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                      result[0] += -0.00014020083457930594;
                    } else {
                      result[0] += 0.0012275694650794818;
                    }
                  } else {
                    result[0] += -0.00014020083457930594;
                  }
                }
              } else {
                if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                  result[0] += 6.760896129660218e-07;
                } else {
                  result[0] += -0.000567277955071411;
                }
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.786764172562814168) ) ) {
                result[0] += -0.00020609284442993036;
              } else {
                result[0] += -0.00018507680401154024;
              }
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9450000000000000622) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
          if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.212199032544347022) ) ) {
            result[0] += 0.0012682651337014644;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8254037945979900703) ) ) {
              result[0] += 4.21595570856836e-06;
            } else {
              result[0] += -0.0004311748300695015;
            }
          }
        } else {
          result[0] += 0.0003252515224399416;
        }
      } else {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
          result[0] += 0.00015266018805374645;
        } else {
          if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1701831610694422292) ) ) {
            result[0] += 0.00011931106052478817;
          } else {
            result[0] += 2.093131589558213e-05;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 8.789927206076283e-05;
      } else {
        result[0] += 8.789927206076283e-05;
      }
    } else {
      result[0] += 8.789927206076283e-05;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 5.5340991353253725e-06;
        } else {
          result[0] += 3.928268560997579e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5259885771356785922) ) ) {
            result[0] += 5.5340991353253725e-06;
          } else {
            result[0] += -0.00012652033769923037;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8517455601758795458) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01911900000000000405) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.045304313006248043) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.743670590552763966) ) ) {
                    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.4725173572200235816) ) ) {
                      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5809002386432161602) ) ) {
                        result[0] += -9.985666939836519e-05;
                      } else {
                        result[0] += -0.000555002799885741;
                      }
                    } else {
                      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6852090990703517681) ) ) {
                        result[0] += 0.0007626848453092271;
                      } else {
                        result[0] += -0.0001224664215031222;
                      }
                    }
                  } else {
                    result[0] += -0.00013428116631649108;
                  }
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7801862323115579256) ) ) {
                    result[0] += 0.0004760034677383885;
                  } else {
                    result[0] += -0.00013428116631649108;
                  }
                }
              } else {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7593447680904524821) ) ) {
                  result[0] += 0.0005498120551311416;
                } else {
                  result[0] += -0.00012693757485505666;
                }
              }
            } else {
              result[0] += 0.0007367040185849605;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006028500000000000872) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8099155601256282644) ) ) {
                    result[0] += 0.0005321019563834388;
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                      result[0] += -0.00013428116631649108;
                    } else {
                      result[0] += 0.0011757380760250816;
                    }
                  }
                } else {
                  result[0] += -0.00013428116631649108;
                }
              } else {
                if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                  result[0] += 6.47543233504708e-07;
                } else {
                  result[0] += -0.0005433259057351339;
                }
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.786764172562814168) ) ) {
                result[0] += -0.00019739103267520084;
              } else {
                result[0] += -0.00017726234779822435;
              }
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9450000000000000622) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
          if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.4612588522637047217) ) ) {
            if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.469327283602055445) ) ) {
              result[0] += 0.00024853859345476767;
            } else {
              result[0] += 0.002001634182838006;
            }
          } else {
            result[0] += -4.181955128263871e-05;
          }
        } else {
          result[0] += 0.0003115185006601707;
        }
      } else {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
          result[0] += 0.00014621445131524142;
        } else {
          if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1701831610694422292) ) ) {
            result[0] += 0.0001142734164871437;
          } else {
            result[0] += 2.0047537658615542e-05;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 8.418792089296141e-05;
      } else {
        result[0] += 8.418792089296141e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        result[0] += 8.418792089296141e-05;
      } else {
        result[0] += 8.418792089296141e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 5.300434113908387e-06;
        } else {
          result[0] += 3.762406162259893e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 5.300434113908387e-06;
          } else {
            result[0] += -0.0001211782979751009;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8517455601758795458) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1547679134652330257) ) ) {
                  result[0] += 0.0007760995959248317;
                } else {
                  result[0] += -0.002692148681415231;
                }
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5645244997236181783) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.05721739154190200877) ) ) {
                    result[0] += 0.00018596217853481225;
                  } else {
                    result[0] += 0.002056899859957729;
                  }
                } else {
                  if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2030091505812350317) ) ) {
                    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.05539262878325219158) ) ) {
                      result[0] += 0.0009186685946391724;
                    } else {
                      result[0] += -0.0007586914159127857;
                    }
                  } else {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6193272217839197458) ) ) {
                      result[0] += 0.0006583505961862234;
                    } else {
                      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6208328749497488142) ) ) {
                        result[0] += -0.0009235360675887428;
                      } else {
                        result[0] += -0.00012861144287352647;
                      }
                    }
                  }
                }
              }
            } else {
              result[0] += 0.0007055983307265997;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006028500000000000872) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8099155601256282644) ) ) {
                    result[0] += 0.0005096351353175272;
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                      result[0] += -0.00012861144287352647;
                    } else {
                      result[0] += 0.0011260951520374097;
                    }
                  }
                } else {
                  result[0] += -0.00012861144287352647;
                }
              } else {
                if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                  result[0] += 6.202021613942563e-07;
                } else {
                  result[0] += -0.000520385178383571;
                }
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.786764172562814168) ) ) {
                result[0] += -0.0001890566355583943;
              } else {
                result[0] += -0.00016977783960965426;
              }
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9450000000000000622) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
          if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.212199032544347022) ) ) {
            result[0] += 0.001204221471539903;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 0.0009744318010771904;
            } else {
              result[0] += -2.4425906089354586e-05;
            }
          }
        } else {
          result[0] += 0.00029836532516609515;
        }
      } else {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
          result[0] += 0.0001400408714673546;
        } else {
          result[0] += 8.950313926773336e-05;
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 8.063327326965967e-05;
      } else {
        result[0] += 8.063327326965967e-05;
      }
    } else {
      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8011796369346734226) ) ) {
        result[0] += 8.063327326965967e-05;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
          result[0] += -0.00042257806988763193;
        } else {
          result[0] += 8.063327326965967e-05;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 5.076635078065328e-06;
        } else {
          result[0] += 3.6035469342290594e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 5.076635078065328e-06;
          } else {
            result[0] += -0.00011606181399112463;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8517455601758795458) ) ) {
              result[0] += -0.0001231811108865754;
            } else {
              result[0] += 0.0006758060113211494;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006028500000000000872) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8099155601256282644) ) ) {
                    result[0] += 0.000488116925777569;
                  } else {
                    result[0] += -0.0001231811108865754;
                  }
                } else {
                  result[0] += -0.0001231811108865754;
                }
              } else {
                if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                  result[0] += 5.940155052138468e-07;
                } else {
                  result[0] += -0.000498413072196329;
                }
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.786764172562814168) ) ) {
                result[0] += -0.00018107413981400183;
              } else {
                result[0] += -0.00016260934812469064;
              }
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6750000000000001554) ) ) {
        result[0] += -8.436249300018593e-05;
      } else {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2070606536698188782) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.009719500000000000708) ) ) {
            result[0] += 9.713807120339571e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
              if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.4314418144595498217) ) ) {
                result[0] += 0.00010566940486747315;
              } else {
                result[0] += -0.0016831613349106557;
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4807908716834171092) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4632663309547739305) ) ) {
                  result[0] += 0.0001346936363518068;
                } else {
                  result[0] += 0.00046236089175310694;
                }
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4839721393467337207) ) ) {
                  result[0] += -0.00155502498850594;
                } else {
                  result[0] += 0.00019723830033338145;
                }
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5180644051256282356) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5012509875628141653) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4891798216080402439) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06607900000000001273) ) ) {
                  result[0] += -0.0007071471283637309;
                } else {
                  result[0] += 0.00018719607487501189;
                }
              } else {
                result[0] += 0.00034769649133135666;
              }
            } else {
              result[0] += -0.0002937040613887427;
            }
          } else {
            if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.03945373639888280493) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01421250000000000117) ) ) {
                result[0] += 0.0001406696038194647;
              } else {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1131639318813234957) ) ) {
                    result[0] += 0.0007190764325588397;
                  } else {
                    result[0] += -0.003103835006073488;
                  }
                } else {
                  result[0] += 0.00024054734688560344;
                }
              }
            } else {
              result[0] += 3.5253889798996246e-05;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 7.722871273238692e-05;
      } else {
        result[0] += 7.722871273238692e-05;
      }
    } else {
      result[0] += 7.722871273238692e-05;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 4.862285458509306e-06;
        } else {
          result[0] += 3.451395183605541e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5259885771356785922) ) ) {
            result[0] += 4.862285458509306e-06;
          } else {
            result[0] += -0.000111161362158084;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            result[0] += -0.00011798006258410568;
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006028500000000000872) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8099155601256282644) ) ) {
                    result[0] += 0.00046750727475274744;
                  } else {
                    result[0] += -0.00011798006258410568;
                  }
                } else {
                  result[0] += -0.00011798006258410568;
                }
              } else {
                if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                  result[0] += 5.689345223196595e-07;
                } else {
                  result[0] += -0.0004773686893001365;
                }
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.786764172562814168) ) ) {
                result[0] += -0.0001734286871896302;
              } else {
                result[0] += -0.00015574353024122974;
              }
            }
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9550000000000000711) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09250981134579591703) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5673593061306533292) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5424744603768845153) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.05721739154190200877) ) ) {
                  result[0] += 3.547209355918279e-05;
                } else {
                  result[0] += 0.0015281119694710537;
                }
              } else {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.009795894273113748066) ) ) {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5493276582412061071) ) ) {
                    result[0] += 8.356283533465916e-05;
                  } else {
                    result[0] += 0.0014912960711018408;
                  }
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5494686760804020631) ) ) {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01696050000000000335) ) ) {
                      result[0] += 0.0002804757126973308;
                    } else {
                      result[0] += 0.0029483455024153543;
                    }
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1475515000000000299) ) ) {
                      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0004235000000000000483) ) ) {
                        result[0] += 0.0018987538633274126;
                      } else {
                        result[0] += -0.0008939710526686818;
                      }
                    } else {
                      result[0] += 0.0005503228788008142;
                    }
                  }
                }
              }
            } else {
              result[0] += -0.0006238744284599688;
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5953483130402011936) ) ) {
              result[0] += -8.684883412620319e-05;
            } else {
              result[0] += 0.003718140040755992;
            }
          }
        } else {
          result[0] += 0.00010078934776477814;
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5531655541959800138) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5499504253266332965) ) ) {
              result[0] += -0.00035945594253614224;
            } else {
              result[0] += 0.0033053223776169567;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005049500000000001036) ) ) {
              result[0] += -0.00038826554033400426;
            } else {
              result[0] += -0.004196150543845793;
            }
          }
        } else {
          result[0] += -2.443848670692391e-05;
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 7.396790218791394e-05;
      } else {
        result[0] += 7.396790218791394e-05;
      }
    } else {
      result[0] += 7.396790218791394e-05;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 4.65698627466458e-06;
        } else {
          result[0] += 3.305667702081427e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 4.65698627466458e-06;
          } else {
            result[0] += -0.0001064678209991243;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8517455601758795458) ) ) {
              result[0] += -0.00011299861697274606;
            } else {
              result[0] += 0.0006522530519195751;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006028500000000000872) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8099155601256282644) ) ) {
                    result[0] += 0.0004477678203815008;
                  } else {
                    result[0] += -0.00011299861697274606;
                  }
                } else {
                  result[0] += -0.00011299861697274606;
                }
              } else {
                if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                  result[0] += 5.44912528117547e-07;
                } else {
                  result[0] += -0.0004572128586434148;
                }
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.786764172562814168) ) ) {
                result[0] += -0.00016610604678953065;
              } else {
                result[0] += -0.0001491676062399626;
              }
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6750000000000001554) ) ) {
        result[0] += -8.229820467554302e-05;
      } else {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2070606536698188782) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.009719500000000000708) ) ) {
            result[0] += 9.15389020827065e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
              if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.4314418144595498217) ) ) {
                result[0] += 9.695214345312564e-05;
              } else {
                result[0] += -0.0016135913231608851;
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4807908716834171092) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4632663309547739305) ) ) {
                  result[0] += 0.00012475089134825047;
                } else {
                  result[0] += 0.00043996353083684776;
                }
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4839721393467337207) ) ) {
                  result[0] += -0.0014922441867087999;
                } else {
                  result[0] += 0.0001866377450872898;
                }
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5180644051256282356) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5012509875628141653) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4891798216080402439) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06607900000000001273) ) ) {
                  result[0] += -0.0006787871446418889;
                } else {
                  result[0] += 0.00017503653123413459;
                }
              } else {
                result[0] += 0.0003287601747538845;
              }
            } else {
              result[0] += -0.0002828007911693321;
            }
          } else {
            if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.03945373639888280493) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01421250000000000117) ) ) {
                result[0] += 9.118832929479088e-05;
              } else {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1131639318813234957) ) ) {
                    result[0] += 0.0006851867755186719;
                  } else {
                    result[0] += -0.0029742802098662318;
                  }
                } else {
                  result[0] += 0.00021187568929671423;
                }
              }
            } else {
              result[0] += 3.682426424218737e-05;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 7.084477211266977e-05;
      } else {
        result[0] += 7.084477211266977e-05;
      }
    } else {
      result[0] += 7.084477211266977e-05;
    }
  }
}

