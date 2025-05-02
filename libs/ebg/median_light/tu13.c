
#include "header.h"

void predict_unit13(union Entry* data, double* result) {
  unsigned int tmp;
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.4142621887637248e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -3.2332801661521715e-06;
        } else {
          result[0] += -3.2332801661521715e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            result[0] += -1.0197943499171828e-06;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -0.0001417307758572499;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                    result[0] += -3.4316113886054025e-06;
                  } else {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8987185122361810441) ) ) {
                      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8323869080904523488) ) ) {
                          result[0] += 0.0017032654488989124;
                        } else {
                          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
                            result[0] += -0.0002956269039111563;
                          } else {
                            result[0] += -0.00024840800231568815;
                          }
                        }
                      } else {
                        result[0] += 7.709723529583122e-05;
                      }
                    } else {
                      result[0] += 0.0015388073636104413;
                    }
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 4.9328518247049165e-06;
                } else {
                  result[0] += -4.538030118285111e-06;
                }
              }
            } else {
              result[0] += -2.7971573670896564e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -3.4316113886054025e-06;
          } else {
            result[0] += -0.0002724650783955128;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -5.044410428639629e-06;
          } else {
            result[0] += -0.00013556636494850146;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
            result[0] += 1.9155629692488596e-07;
          } else {
            result[0] += -0.0017924155290085905;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 2.1514575427457676e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 2.1514575427457676e-06;
            } else {
              result[0] += 2.1514575427457676e-06;
            }
          } else {
            result[0] += 2.1514575427457676e-06;
          }
        } else {
          result[0] += 2.1514575427457676e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 2.1514575427457676e-06;
            } else {
              result[0] += 2.1514575427457676e-06;
            }
          } else {
            result[0] += 2.1514575427457676e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 2.1514575427457676e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 2.1514575427457676e-06;
              } else {
                result[0] += 2.1514575427457676e-06;
              }
            } else {
              result[0] += 2.1514575427457676e-06;
            }
          }
        }
      } else {
        result[0] += 2.1514575427457676e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.3545481148835295e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -3.096762105886739e-06;
        } else {
          result[0] += -3.096762105886739e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            result[0] += -9.767358027584085e-07;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -0.0001357465092284254;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                    result[0] += -3.286719233801926e-06;
                  } else {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8987185122361810441) ) ) {
                      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8323869080904523488) ) ) {
                          result[0] += 0.001631348855454581;
                        } else {
                          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
                            result[0] += -0.0002831447157275534;
                          } else {
                            result[0] += -0.00023791952717964595;
                          }
                        }
                      } else {
                        result[0] += 7.384197609355208e-05;
                      }
                    } else {
                      result[0] += 0.0014738346468624697;
                    }
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 4.724573133073047e-06;
                } else {
                  result[0] += -4.3464218946428e-06;
                }
              }
            } else {
              result[0] += -2.6790536215467044e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -3.286719233801926e-06;
          } else {
            result[0] += -0.0002609608467542174;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -4.83142142319873e-06;
          } else {
            result[0] += -0.0001298423768531462;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
            result[0] += 1.8346825854158264e-07;
          } else {
            result[0] += -0.0017167347718099117;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 2.060617035461719e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 2.060617035461719e-06;
            } else {
              result[0] += 2.060617035461719e-06;
            }
          } else {
            result[0] += 2.060617035461719e-06;
          }
        } else {
          result[0] += 2.060617035461719e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 2.060617035461719e-06;
            } else {
              result[0] += 2.060617035461719e-06;
            }
          } else {
            result[0] += 2.060617035461719e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 2.060617035461719e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 2.060617035461719e-06;
              } else {
                result[0] += 2.060617035461719e-06;
              }
            } else {
              result[0] += 2.060617035461719e-06;
            }
          }
        }
      } else {
        result[0] += 2.060617035461719e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.297355334895994e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -2.9660082169337185e-06;
        } else {
          result[0] += -2.9660082169337185e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7847910031909549611) ) ) {
              result[0] += 5.222825788974779e-06;
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7936293736432161738) ) ) {
                result[0] += -0.00025107938303090514;
              } else {
                result[0] += 2.154023145452974e-05;
              }
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -0.00013001491494171047;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    result[0] += -3.1479448278185236e-06;
                  } else {
                    result[0] += 7.072416296743072e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 4.525088545730024e-06;
                } else {
                  result[0] += -4.162903901873887e-06;
                }
              }
            } else {
              result[0] += -2.565936543852891e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -3.1479448278185236e-06;
          } else {
            result[0] += -0.00024994235569456214;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -4.6274254045657945e-06;
          } else {
            result[0] += -0.00012436007141800105;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
            result[0] += 1.7572171958137287e-07;
          } else {
            result[0] += -0.0016442494661778303;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.9736120664601883e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 1.9736120664601883e-06;
            } else {
              result[0] += 1.9736120664601883e-06;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.9736120664601883e-06;
            } else {
              result[0] += 1.9736120664601883e-06;
            }
          }
        } else {
          result[0] += 1.9736120664601883e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 1.9736120664601883e-06;
              } else {
                result[0] += 1.9736120664601883e-06;
              }
            } else {
              result[0] += 1.9736120664601883e-06;
            }
          } else {
            result[0] += 1.9736120664601883e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.9736120664601883e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.9736120664601883e-06;
              } else {
                result[0] += 1.9736120664601883e-06;
              }
            } else {
              result[0] += 1.9736120664601883e-06;
            }
          }
        }
      } else {
        result[0] += 1.9736120664601883e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.2425773927772302e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -2.840775119985915e-06;
        } else {
          result[0] += -2.840775119985915e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08005850000000001854) ) ) {
              result[0] += -7.386537581387391e-06;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9993516786272610419) ) ) {
                result[0] += 8.227223488951265e-05;
              } else {
                result[0] += -0.00024047811478856496;
              }
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -0.00012452532446971038;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    result[0] += -3.0150298623245873e-06;
                  } else {
                    result[0] += 6.773799256274869e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 4.334026751191043e-06;
                } else {
                  result[0] += -3.987134547982264e-06;
                }
              }
            } else {
              result[0] += -2.457595583054631e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -3.0150298623245873e-06;
          } else {
            result[0] += -0.00023938909590136645;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -4.432042663884203e-06;
          } else {
            result[0] += -0.00011910924413053504;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 1.6830226099102694e-07;
          } else {
            result[0] += -0.0010480963656820162;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.8902806886700388e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 1.8902806886700388e-06;
            } else {
              result[0] += 1.8902806886700388e-06;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.8902806886700388e-06;
            } else {
              result[0] += 1.8902806886700388e-06;
            }
          }
        } else {
          result[0] += 1.8902806886700388e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 1.8902806886700388e-06;
              } else {
                result[0] += 1.8902806886700388e-06;
              }
            } else {
              result[0] += 1.8902806886700388e-06;
            }
          } else {
            result[0] += 1.8902806886700388e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.8902806886700388e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.8902806886700388e-06;
              } else {
                result[0] += 1.8902806886700388e-06;
              }
            } else {
              result[0] += 1.8902806886700388e-06;
            }
          }
        }
      } else {
        result[0] += 1.8902806886700388e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.1901123273713671e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -2.7208297118859153e-06;
        } else {
          result[0] += -2.7208297118859153e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.4612588522637047217) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.3684892717336683554) ) ) {
                result[0] += -4.0998746885555426e-05;
              } else {
                result[0] += 0.0001424701244573498;
              }
            } else {
              result[0] += -7.30384158073725e-06;
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -0.00011926751973985986;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    result[0] += -2.8877269354839767e-06;
                  } else {
                    result[0] += 6.487790655852685e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 4.151032115772495e-06;
                } else {
                  result[0] += -3.81878666393374e-06;
                }
              }
            } else {
              result[0] += -2.353829078243871e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -2.8877269354839767e-06;
          } else {
            result[0] += -0.00022928142401964366;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -4.244909524658873e-06;
          } else {
            result[0] += -0.00011408012134105155;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 1.6119607252975212e-07;
          } else {
            result[0] += -0.001003842828883062;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.8104677928770083e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 1.8104677928770083e-06;
            } else {
              result[0] += 1.8104677928770083e-06;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.8104677928770083e-06;
            } else {
              result[0] += 1.8104677928770083e-06;
            }
          }
        } else {
          result[0] += 1.8104677928770083e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 1.8104677928770083e-06;
              } else {
                result[0] += 1.8104677928770083e-06;
              }
            } else {
              result[0] += 1.8104677928770083e-06;
            }
          } else {
            result[0] += 1.8104677928770083e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.8104677928770083e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.8104677928770083e-06;
              } else {
                result[0] += 1.8104677928770083e-06;
              }
            } else {
              result[0] += 1.8104677928770083e-06;
            }
          }
        }
      } else {
        result[0] += 1.8104677928770083e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.1398624826065803e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -2.6059487317383876e-06;
        } else {
          result[0] += -2.6059487317383876e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
              result[0] += 4.5667440531072685e-06;
            } else {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
                result[0] += -4.572926323010076e-05;
              } else {
                result[0] += -1.081571706134678e-05;
              }
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -0.00011423171411497021;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    result[0] += -2.76579909145256e-06;
                  } else {
                    result[0] += 6.213858132152094e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 3.975764021631702e-06;
                } else {
                  result[0] += -3.6575468946785727e-06;
                }
              }
            } else {
              result[0] += -2.25444388319575e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -2.76579909145256e-06;
          } else {
            result[0] += -0.00021960052609136229;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -4.065677665825469e-06;
          } else {
            result[0] += -0.00010926334207046387;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 1.5438992706344244e-07;
          } else {
            result[0] += -0.0009614577992017164;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.7340248190054464e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 1.7340248190054464e-06;
            } else {
              result[0] += 1.7340248190054464e-06;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.7340248190054464e-06;
            } else {
              result[0] += 1.7340248190054464e-06;
            }
          }
        } else {
          result[0] += 1.7340248190054464e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 1.7340248190054464e-06;
              } else {
                result[0] += 1.7340248190054464e-06;
              }
            } else {
              result[0] += 1.7340248190054464e-06;
            }
          } else {
            result[0] += 1.7340248190054464e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.7340248190054464e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.7340248190054464e-06;
              } else {
                result[0] += 1.7340248190054464e-06;
              }
            } else {
              result[0] += 1.7340248190054464e-06;
            }
          }
        }
      } else {
        result[0] += 1.7340248190054464e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.091734325719715e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -2.4959183453424517e-06;
        } else {
          result[0] += -2.4959183453424517e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
              result[0] += 4.373923447460615e-06;
            } else {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
                result[0] += -4.379844684774894e-05;
              } else {
                result[0] += -1.0359047475752223e-05;
              }
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -0.00010940853417683066;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    result[0] += -2.6490193793194446e-06;
                  } else {
                    result[0] += 5.951491799705428e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 3.807896232756441e-06;
                } else {
                  result[0] += -3.5031151158867108e-06;
                }
              }
            } else {
              result[0] += -2.1592550068549235e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -2.6490193793194446e-06;
          } else {
            result[0] += -0.00021032838253600363;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -3.894013473401506e-06;
          } else {
            result[0] += -0.00010464994058619711;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 1.4787115594429633e-07;
          } else {
            result[0] += -0.0009208623830827719;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.660809479606744e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 1.660809479606744e-06;
            } else {
              result[0] += 1.660809479606744e-06;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.660809479606744e-06;
            } else {
              result[0] += 1.660809479606744e-06;
            }
          }
        } else {
          result[0] += 1.660809479606744e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 1.660809479606744e-06;
              } else {
                result[0] += 1.660809479606744e-06;
              }
            } else {
              result[0] += 1.660809479606744e-06;
            }
          } else {
            result[0] += 1.660809479606744e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.660809479606744e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.660809479606744e-06;
              } else {
                result[0] += 1.660809479606744e-06;
              }
            } else {
              result[0] += 1.660809479606744e-06;
            }
          }
        }
      } else {
        result[0] += 1.660809479606744e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.045638273162094e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -2.390533747170583e-06;
        } else {
          result[0] += -2.390533747170583e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
              result[0] += 4.189244262822121e-06;
            } else {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
                result[0] += -4.194915489065551e-05;
              } else {
                result[0] += -9.92165974722028e-06;
              }
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -0.00010478900227895653;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    result[0] += -2.5371704306709358e-06;
                  } else {
                    result[0] += 5.700203301824269e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 3.647116287724161e-06;
                } else {
                  result[0] += -3.3552038753100986e-06;
                }
              }
            } else {
              result[0] += -2.068085269001617e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -2.5371704306709358e-06;
          } else {
            result[0] += -0.00020144773460973662;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -3.729597419512546e-06;
          } else {
            result[0] += -0.00010023132971378359;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 1.4162762542997512e-07;
          } else {
            result[0] += -0.0008819810180758354;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.5906854949919336e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 1.5906854949919336e-06;
            } else {
              result[0] += 1.5906854949919336e-06;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.5906854949919336e-06;
            } else {
              result[0] += 1.5906854949919336e-06;
            }
          }
        } else {
          result[0] += 1.5906854949919336e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 1.5906854949919336e-06;
              } else {
                result[0] += 1.5906854949919336e-06;
              }
            } else {
              result[0] += 1.5906854949919336e-06;
            }
          } else {
            result[0] += 1.5906854949919336e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.5906854949919336e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.5906854949919336e-06;
              } else {
                result[0] += 1.5906854949919336e-06;
              }
            } else {
              result[0] += 1.5906854949919336e-06;
            }
          }
        }
      } else {
        result[0] += 1.5906854949919336e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.0014885238503169e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -2.2895987791528843e-06;
        } else {
          result[0] += -2.2895987791528843e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            result[0] += -1.4585225949104737e-06;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -0.00010036451983600869;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8987185122361810441) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                        result[0] += -2.430044054990916e-06;
                      } else {
                        result[0] += -2.430044054990916e-06;
                      }
                    } else {
                      result[0] += -2.430044054990916e-06;
                    }
                  } else {
                    result[0] += 5.459524901594671e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 3.4931249181005843e-06;
                } else {
                  result[0] += -3.21353785773221e-06;
                }
              }
            } else {
              result[0] += -1.9807649704567187e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -2.430044054990916e-06;
          } else {
            result[0] += -0.00019294205228078727;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -3.5721234676376305e-06;
          } else {
            result[0] += -9.59992848530892e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 1.3564771409841019e-07;
          } else {
            result[0] += -0.0008447413321868379;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.523522339586571e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 1.523522339586571e-06;
            } else {
              result[0] += 1.523522339586571e-06;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.523522339586571e-06;
            } else {
              result[0] += 1.523522339586571e-06;
            }
          }
        } else {
          result[0] += 1.523522339586571e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 1.523522339586571e-06;
              } else {
                result[0] += 1.523522339586571e-06;
              }
            } else {
              result[0] += 1.523522339586571e-06;
            }
          } else {
            result[0] += 1.523522339586571e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.523522339586571e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.523522339586571e-06;
              } else {
                result[0] += 1.523522339586571e-06;
              }
            } else {
              result[0] += 1.523522339586571e-06;
            }
          }
        }
      } else {
        result[0] += 1.523522339586571e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 9.592028994602851e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -2.1929255655575735e-06;
        } else {
          result[0] += -2.1929255655575735e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            result[0] += -1.3969397238693503e-06;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -9.612685131878028e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8987185122361810441) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                        result[0] += -2.327440852144541e-06;
                      } else {
                        result[0] += -2.327440852144541e-06;
                      }
                    } else {
                      result[0] += -2.327440852144541e-06;
                    }
                  } else {
                    result[0] += 5.2290086112530784e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 3.3456354913951327e-06;
                } else {
                  result[0] += -3.077853372508901e-06;
                }
              }
            } else {
              result[0] += -1.8971315772112446e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -2.327440852144541e-06;
          } else {
            result[0] += -0.00018479550346118734;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -3.421298502966901e-06;
          } else {
            result[0] += -9.194592866941898e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 1.2992029121621954e-07;
          } else {
            result[0] += -0.000809074009168117;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.4591949989641291e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 1.4591949989641291e-06;
            } else {
              result[0] += 1.4591949989641291e-06;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.4591949989641291e-06;
            } else {
              result[0] += 1.4591949989641291e-06;
            }
          }
        } else {
          result[0] += 1.4591949989641291e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 1.4591949989641291e-06;
              } else {
                result[0] += 1.4591949989641291e-06;
              }
            } else {
              result[0] += 1.4591949989641291e-06;
            }
          } else {
            result[0] += 1.4591949989641291e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.4591949989641291e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.4591949989641291e-06;
              } else {
                result[0] += 1.4591949989641291e-06;
              }
            } else {
              result[0] += 1.4591949989641291e-06;
            }
          }
        }
      } else {
        result[0] += 1.4591949989641291e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 9.187026914656109e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -2.1003341632873805e-06;
        } else {
          result[0] += -2.1003341632873805e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            result[0] += -1.3379570525219934e-06;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -9.206810892495933e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8987185122361810441) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                        result[0] += -2.229169841223951e-06;
                      } else {
                        result[0] += -2.229169841223951e-06;
                      }
                    } else {
                      result[0] += -2.229169841223951e-06;
                    }
                  } else {
                    result[0] += 5.008225358322364e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 3.2043734775363218e-06;
                } else {
                  result[0] += -2.947897862746708e-06;
                }
              }
            } else {
              result[0] += -1.8170294178931636e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -2.229169841223951e-06;
          } else {
            result[0] += -0.0001769929245376558;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -3.2768417868111004e-06;
          } else {
            result[0] += -8.806371643100668e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 1.2443469602046998e-07;
          } else {
            result[0] += -0.0007749126594963239;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.397583737159449e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 1.397583737159449e-06;
            } else {
              result[0] += 1.397583737159449e-06;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.397583737159449e-06;
            } else {
              result[0] += 1.397583737159449e-06;
            }
          }
        } else {
          result[0] += 1.397583737159449e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 1.397583737159449e-06;
              } else {
                result[0] += 1.397583737159449e-06;
              }
            } else {
              result[0] += 1.397583737159449e-06;
            }
          } else {
            result[0] += 1.397583737159449e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.397583737159449e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.397583737159449e-06;
              } else {
                result[0] += 1.397583737159449e-06;
              }
            } else {
              result[0] += 1.397583737159449e-06;
            }
          }
        }
      } else {
        result[0] += 1.397583737159449e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 8.799125146310925e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -2.01165222694211e-06;
        } else {
          result[0] += -2.01165222694211e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            result[0] += -1.2814647932258298e-06;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -8.818073789713445e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8987185122361810441) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                        result[0] += -2.1350481050651476e-06;
                      } else {
                        result[0] += -2.1350481050651476e-06;
                      }
                    } else {
                      result[0] += -2.1350481050651476e-06;
                    }
                  } else {
                    result[0] += 4.796764186955974e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 3.069075937874049e-06;
                } else {
                  result[0] += -2.823429435204999e-06;
                }
              }
            } else {
              result[0] += -1.740309394007532e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -2.1350481050651476e-06;
          } else {
            result[0] += -0.00016951979214673783;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -3.1384844340474217e-06;
          } else {
            result[0] += -8.434542196559625e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 1.1918071787522066e-07;
          } else {
            result[0] += -0.0007421936967980025;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.338573873784112e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 1.338573873784112e-06;
            } else {
              result[0] += 1.338573873784112e-06;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.338573873784112e-06;
            } else {
              result[0] += 1.338573873784112e-06;
            }
          }
        } else {
          result[0] += 1.338573873784112e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 1.338573873784112e-06;
              } else {
                result[0] += 1.338573873784112e-06;
              }
            } else {
              result[0] += 1.338573873784112e-06;
            }
          } else {
            result[0] += 1.338573873784112e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.338573873784112e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.338573873784112e-06;
              } else {
                result[0] += 1.338573873784112e-06;
              }
            } else {
              result[0] += 1.338573873784112e-06;
            }
          }
        }
      } else {
        result[0] += 1.338573873784112e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 8.427601666968458e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -1.9267146880224333e-06;
        } else {
          result[0] += -1.9267146880224333e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8643464628140704598) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8168185667587940513) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
                result[0] += -2.4518215777353146e-06;
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002740500000000000314) ) ) {
                  result[0] += 0.0005527944513666308;
                } else {
                  result[0] += 0.004496080711381585;
                }
              }
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
                result[0] += -2.1004825630229143e-05;
              } else {
                result[0] += 0.0023124959134157483;
              }
            }
          } else {
            result[0] += 0.0007792745899621913;
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -8.445750246071494e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                    result[0] += -2.0449004497743515e-06;
                  } else {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8987185122361810441) ) ) {
                      result[0] += -0.00022677086018904456;
                    } else {
                      result[0] += 0.0014127083028788233;
                    }
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 2.9394910357576144e-06;
                } else {
                  result[0] += -2.7042164100469636e-06;
                }
              }
            } else {
              result[0] += -2.0449004497743515e-06;
            }
          } else {
            result[0] += -5.8830272860707666e-05;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -3.00596891262904e-06;
          } else {
            result[0] += -8.078412420997529e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 1.141485772659124e-07;
          } else {
            result[0] += -0.0007108562194928221;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.282055570582775e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            result[0] += 1.282055570582775e-06;
          } else {
            result[0] += 1.282055570582775e-06;
          }
        } else {
          result[0] += 1.282055570582775e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.282055570582775e-06;
            } else {
              result[0] += 1.282055570582775e-06;
            }
          } else {
            result[0] += 1.282055570582775e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.282055570582775e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.282055570582775e-06;
              } else {
                result[0] += 1.282055570582775e-06;
              }
            } else {
              result[0] += 1.282055570582775e-06;
            }
          }
        }
      } else {
        result[0] += 1.282055570582775e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 8.071764939820811e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -1.8453634476792156e-06;
        } else {
          result[0] += -1.8453634476792156e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            result[0] += -1.4332765864557534e-06;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -8.089147235559102e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8987185122361810441) ) ) {
                      result[0] += -1.9585590786301046e-06;
                    } else {
                      result[0] += -1.9585590786301046e-06;
                    }
                  } else {
                    result[0] += 5.5517209887118716e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 2.8153775677785052e-06;
                } else {
                  result[0] += -2.590036889601363e-06;
                }
              }
            } else {
              result[0] += -1.4184309662704206e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -1.9585590786301046e-06;
          } else {
            result[0] += -0.0001598782187802702;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -2.879048564226744e-06;
          } else {
            result[0] += -7.737319432742474e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 1.0932890759622679e-07;
          } else {
            result[0] += -0.0006808418974341621;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.2279236269663954e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 1.2279236269663954e-06;
            } else {
              result[0] += 1.2279236269663954e-06;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.2279236269663954e-06;
            } else {
              result[0] += 1.2279236269663954e-06;
            }
          }
        } else {
          result[0] += 1.2279236269663954e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8011796369346734226) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 1.2279236269663954e-06;
              } else {
                result[0] += 1.2279236269663954e-06;
              }
            } else {
              result[0] += 1.2279236269663954e-06;
            }
          } else {
            result[0] += 1.2279236269663954e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.2279236269663954e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.2279236269663954e-06;
              } else {
                result[0] += 1.2279236269663954e-06;
              }
            } else {
              result[0] += 1.2279236269663954e-06;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
          result[0] += -0.0004222282272360057;
        } else {
          result[0] += 1.2279236269663954e-06;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 7.73095262666822e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -1.7674470824353132e-06;
        } else {
          result[0] += -1.7674470824353132e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            result[0] += -1.3727596719435997e-06;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -7.747600993646477e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8987185122361810441) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                        result[0] += -1.8758632797541268e-06;
                      } else {
                        result[0] += -1.8758632797541268e-06;
                      }
                    } else {
                      result[0] += -1.8758632797541268e-06;
                    }
                  } else {
                    result[0] += 5.3173119237480594e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 2.696504514805401e-06;
                } else {
                  result[0] += -2.4806783453323553e-06;
                }
              }
            } else {
              result[0] += -1.3585408750364762e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -1.8758632797541268e-06;
          } else {
            result[0] += -0.00015312771675602153;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -2.7574871451104033e-06;
          } else {
            result[0] += -7.41062833691053e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 1.0471273775353223e-07;
          } else {
            result[0] += -0.000652094863336046;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.1760772842129568e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 1.1760772842129568e-06;
            } else {
              result[0] += 1.1760772842129568e-06;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.1760772842129568e-06;
            } else {
              result[0] += 1.1760772842129568e-06;
            }
          }
        } else {
          result[0] += 1.1760772842129568e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 1.1760772842129568e-06;
              } else {
                result[0] += 1.1760772842129568e-06;
              }
            } else {
              result[0] += 1.1760772842129568e-06;
            }
          } else {
            result[0] += 1.1760772842129568e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.1760772842129568e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.1760772842129568e-06;
              } else {
                result[0] += 1.1760772842129568e-06;
              }
            } else {
              result[0] += 1.1760772842129568e-06;
            }
          }
        }
      } else {
        result[0] += 1.1760772842129568e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 7.4045303550546e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -1.692820562332987e-06;
        } else {
          result[0] += -1.692820562332987e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            result[0] += -1.314797949484418e-06;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -7.420475781784069e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8987185122361810441) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                        result[0] += -1.7966591269695802e-06;
                      } else {
                        result[0] += -1.7966591269695802e-06;
                      }
                    } else {
                      result[0] += -1.7966591269695802e-06;
                    }
                  } else {
                    result[0] += 5.092800259941282e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 2.582650611975734e-06;
                } else {
                  result[0] += -2.375937222248602e-06;
                }
              }
            } else {
              result[0] += -1.3011795096364117e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -1.7966591269695802e-06;
          } else {
            result[0] += -0.00014666223965841444;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -2.6410583864157005e-06;
          } else {
            result[0] += -7.097731045641476e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 1.0029147541046531e-07;
          } else {
            result[0] += -0.0006245616087843305;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.1264200379138046e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 1.1264200379138046e-06;
            } else {
              result[0] += 1.1264200379138046e-06;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.1264200379138046e-06;
            } else {
              result[0] += 1.1264200379138046e-06;
            }
          }
        } else {
          result[0] += 1.1264200379138046e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 1.1264200379138046e-06;
              } else {
                result[0] += 1.1264200379138046e-06;
              }
            } else {
              result[0] += 1.1264200379138046e-06;
            }
          } else {
            result[0] += 1.1264200379138046e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.1264200379138046e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.1264200379138046e-06;
              } else {
                result[0] += 1.1264200379138046e-06;
              }
            } else {
              result[0] += 1.1264200379138046e-06;
            }
          }
        }
      } else {
        result[0] += 1.1264200379138046e-06;
      }
    }
  }
}

