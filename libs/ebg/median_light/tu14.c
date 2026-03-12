
#include "header.h"

void predict_unit14(union Entry* data, double* result) {
  unsigned int tmp;
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 7.091890537502151e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -1.6213449809817738e-06;
        } else {
          result[0] += -1.6213449809817738e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            result[0] += -1.2592835317794186e-06;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -7.10716270406793e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8987185122361810441) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                        result[0] += -1.720799193289925e-06;
                      } else {
                        result[0] += -1.720799193289925e-06;
                      }
                    } else {
                      result[0] += -1.720799193289925e-06;
                    }
                  } else {
                    result[0] += 4.8777681015515536e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 2.473603936843397e-06;
                } else {
                  result[0] += -2.2756185600153206e-06;
                }
              }
            } else {
              result[0] += -1.2462401002489557e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -1.720799193289925e-06;
          } else {
            result[0] += -0.000140469752944163;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -2.5295455729776147e-06;
          } else {
            result[0] += -6.79804514623185e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 9.605689103156577e-08;
          } else {
            result[0] += -0.0005981908846385923;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.0788594583421446e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 1.0788594583421446e-06;
            } else {
              result[0] += 1.0788594583421446e-06;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.0788594583421446e-06;
            } else {
              result[0] += 1.0788594583421446e-06;
            }
          }
        } else {
          result[0] += 1.0788594583421446e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 1.0788594583421446e-06;
              } else {
                result[0] += 1.0788594583421446e-06;
              }
            } else {
              result[0] += 1.0788594583421446e-06;
            }
          } else {
            result[0] += 1.0788594583421446e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.0788594583421446e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.0788594583421446e-06;
              } else {
                result[0] += 1.0788594583421446e-06;
              }
            } else {
              result[0] += 1.0788594583421446e-06;
            }
          }
        }
      } else {
        result[0] += 1.0788594583421446e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 6.792451240552458e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -1.5528872970044257e-06;
        } else {
          result[0] += -1.5528872970044257e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            result[0] += -1.2061130868314124e-06;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -6.807078573868735e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8987185122361810441) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                        result[0] += -1.6481422765050707e-06;
                      } else {
                        result[0] += -1.6481422765050707e-06;
                      }
                    } else {
                      result[0] += -1.6481422765050707e-06;
                    }
                  } else {
                    result[0] += 4.6718151975565876e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 2.369161514915995e-06;
                } else {
                  result[0] += -2.1795356300640356e-06;
                }
              }
            } else {
              result[0] += -1.193620385170698e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -1.6481422765050707e-06;
          } else {
            result[0] += -0.0001345387302017941;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -2.4227411399467316e-06;
          } else {
            result[0] += -6.511012817058603e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 9.200110255519562e-08;
          } else {
            result[0] += -0.0005729336056393208;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.0333070184108779e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 1.0333070184108779e-06;
            } else {
              result[0] += 1.0333070184108779e-06;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.0333070184108779e-06;
            } else {
              result[0] += 1.0333070184108779e-06;
            }
          }
        } else {
          result[0] += 1.0333070184108779e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 1.0333070184108779e-06;
              } else {
                result[0] += 1.0333070184108779e-06;
              }
            } else {
              result[0] += 1.0333070184108779e-06;
            }
          } else {
            result[0] += 1.0333070184108779e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.0333070184108779e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.0333070184108779e-06;
              } else {
                result[0] += 1.0333070184108779e-06;
              }
            } else {
              result[0] += 1.0333070184108779e-06;
            }
          }
        }
      } else {
        result[0] += 1.0333070184108779e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 6.505655101599835e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -1.4873200863997722e-06;
        } else {
          result[0] += -1.4873200863997722e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8643464628140704598) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8168185667587940513) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
                result[0] += -2.0702099265941287e-06;
              } else {
                result[0] += 0.0010052104393506245;
              }
            } else {
              result[0] += -1.9839854667434973e-05;
            }
          } else {
            result[0] += 0.0007466495433970468;
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -6.519664828314859e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                    result[0] += -1.578553136354042e-06;
                  } else {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8987185122361810441) ) ) {
                      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.555383890033505745) ) ) {
                        result[0] += 4.474558196642889e-05;
                      } else {
                        result[0] += -0.0002601316148870204;
                      }
                    } else {
                      result[0] += 0.0013534398443147322;
                    }
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 2.269128941847413e-06;
                } else {
                  result[0] += -2.087509588024564e-06;
                }
              }
            } else {
              result[0] += -1.578553136354042e-06;
            }
          } else {
            result[0] += -5.359421004130235e-05;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -2.3204462864375254e-06;
          } else {
            result[0] += -6.236099789275446e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 8.81165607222303e-08;
          } else {
            result[0] += -0.0005487427590428643;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 9.896779288916377e-07;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 9.896779288916377e-07;
            } else {
              result[0] += 9.896779288916377e-07;
            }
          } else {
            result[0] += 9.896779288916377e-07;
          }
        } else {
          result[0] += 9.896779288916377e-07;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 9.896779288916377e-07;
            } else {
              result[0] += 9.896779288916377e-07;
            }
          } else {
            result[0] += 9.896779288916377e-07;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 9.896779288916377e-07;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 9.896779288916377e-07;
              } else {
                result[0] += 9.896779288916377e-07;
              }
            } else {
              result[0] += 9.896779288916377e-07;
            }
          }
        }
      } else {
        result[0] += 9.896779288916377e-07;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 6.230968291429466e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -1.4245213053616509e-06;
        } else {
          result[0] += -1.4245213053616509e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            result[0] += -1.0727795848653185e-06;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -6.24438648860901e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8987185122361810441) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                        result[0] += -1.5119022427949453e-06;
                      } else {
                        result[0] += -1.5119022427949453e-06;
                      }
                    } else {
                      result[0] += -1.5119022427949453e-06;
                    }
                  } else {
                    result[0] += 4.285629933653115e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 2.173320021582459e-06;
                } else {
                  result[0] += -1.999369140832285e-06;
                }
              }
            } else {
              result[0] += -9.169327944472983e-06;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -1.5119022427949453e-06;
          } else {
            result[0] += -0.00012659523543666676;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -2.222470605489487e-06;
          } else {
            result[0] += -5.972794352349258e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 8.439603502421297e-08;
          } else {
            result[0] += -0.0005255733171140574;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 9.478909805903254e-07;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 9.478909805903254e-07;
            } else {
              result[0] += 9.478909805903254e-07;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 9.478909805903254e-07;
            } else {
              result[0] += 9.478909805903254e-07;
            }
          }
        } else {
          result[0] += 9.478909805903254e-07;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 9.478909805903254e-07;
              } else {
                result[0] += 9.478909805903254e-07;
              }
            } else {
              result[0] += 9.478909805903254e-07;
            }
          } else {
            result[0] += 9.478909805903254e-07;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 9.478909805903254e-07;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 9.478909805903254e-07;
              } else {
                result[0] += 9.478909805903254e-07;
              }
            } else {
              result[0] += 9.478909805903254e-07;
            }
          }
        }
      } else {
        result[0] += 9.478909805903254e-07;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 5.967879520577922e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -1.3643740631119437e-06;
        } else {
          result[0] += -1.3643740631119437e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            result[0] += -1.0274838540585907e-06;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -5.980731164243168e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8987185122361810441) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                        result[0] += -1.4480655349036722e-06;
                      } else {
                        result[0] += -1.4480655349036722e-06;
                      }
                    } else {
                      result[0] += -1.4480655349036722e-06;
                    }
                  } else {
                    result[0] += 4.1046787461616835e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 2.0815564197800433e-06;
                } else {
                  result[0] += -1.9149502278910688e-06;
                }
              }
            } else {
              result[0] += -8.782173475762751e-06;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -1.4480655349036722e-06;
          } else {
            result[0] += -0.00012125003332223736;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -2.1286317296523175e-06;
          } else {
            result[0] += -5.720606401585515e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 8.083260024481698e-08;
          } else {
            result[0] += -0.0005033821533136556;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 9.078683931978904e-07;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 9.078683931978904e-07;
            } else {
              result[0] += 9.078683931978904e-07;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 9.078683931978904e-07;
            } else {
              result[0] += 9.078683931978904e-07;
            }
          }
        } else {
          result[0] += 9.078683931978904e-07;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 9.078683931978904e-07;
              } else {
                result[0] += 9.078683931978904e-07;
              }
            } else {
              result[0] += 9.078683931978904e-07;
            }
          } else {
            result[0] += 9.078683931978904e-07;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 9.078683931978904e-07;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 9.078683931978904e-07;
              } else {
                result[0] += 9.078683931978904e-07;
              }
            } else {
              result[0] += 9.078683931978904e-07;
            }
          }
        }
      } else {
        result[0] += 9.078683931978904e-07;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 5.715899087648316e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -1.30676640432554e-06;
        } else {
          result[0] += -1.30676640432554e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            result[0] += -9.841006346981296e-07;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -5.728208099258334e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8987185122361810441) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                        result[0] += -1.3869241899525732e-06;
                      } else {
                        result[0] += -1.3869241899525732e-06;
                      }
                    } else {
                      result[0] += -1.3869241899525732e-06;
                    }
                  } else {
                    result[0] += 3.931367819906398e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 1.9936673318697972e-06;
                } else {
                  result[0] += -1.8340957156983856e-06;
                }
              }
            } else {
              result[0] += -8.411365742990889e-06;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -1.3869241899525732e-06;
          } else {
            result[0] += -0.00011613052047285439;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -2.0387549915355003e-06;
          } else {
            result[0] += -5.4790665258698277e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 7.741962356956492e-08;
          } else {
            result[0] += -0.00048212796202456846;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 8.695356704975892e-07;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 8.695356704975892e-07;
            } else {
              result[0] += 8.695356704975892e-07;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 8.695356704975892e-07;
            } else {
              result[0] += 8.695356704975892e-07;
            }
          }
        } else {
          result[0] += 8.695356704975892e-07;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 8.695356704975892e-07;
              } else {
                result[0] += 8.695356704975892e-07;
              }
            } else {
              result[0] += 8.695356704975892e-07;
            }
          } else {
            result[0] += 8.695356704975892e-07;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 8.695356704975892e-07;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 8.695356704975892e-07;
              } else {
                result[0] += 8.695356704975892e-07;
              }
            } else {
              result[0] += 8.695356704975892e-07;
            }
          }
        }
      } else {
        result[0] += 8.695356704975892e-07;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 5.474557967785623e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -1.2515911007418843e-06;
        } else {
          result[0] += -1.2515911007418843e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            result[0] += -9.425491752329638e-07;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -5.4863472587738385e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8987185122361810441) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                        result[0] += -1.3283644022392676e-06;
                      } else {
                        result[0] += -1.3283644022392676e-06;
                      }
                    } else {
                      result[0] += -1.3283644022392676e-06;
                    }
                  } else {
                    result[0] += 3.765374561857801e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 1.9094891651242594e-06;
                } else {
                  result[0] += -1.7566551053641947e-06;
                }
              }
            } else {
              result[0] += -8.056214541608663e-06;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -1.3283644022392676e-06;
          } else {
            result[0] += -0.00011122716766150971;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -1.9526730986904098e-06;
          } else {
            result[0] += -5.24772513392757e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 7.415075223981128e-08;
          } else {
            result[0] += -0.00046177118166747277;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 8.328214617177792e-07;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 8.328214617177792e-07;
            } else {
              result[0] += 8.328214617177792e-07;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 8.328214617177792e-07;
            } else {
              result[0] += 8.328214617177792e-07;
            }
          }
        } else {
          result[0] += 8.328214617177792e-07;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 8.328214617177792e-07;
              } else {
                result[0] += 8.328214617177792e-07;
              }
            } else {
              result[0] += 8.328214617177792e-07;
            }
          } else {
            result[0] += 8.328214617177792e-07;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 8.328214617177792e-07;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 8.328214617177792e-07;
              } else {
                result[0] += 8.328214617177792e-07;
              }
            } else {
              result[0] += 8.328214617177792e-07;
            }
          }
        }
      } else {
        result[0] += 8.328214617177792e-07;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 5.2434069396787625e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -1.1987454515749893e-06;
        } else {
          result[0] += -1.1987454515749893e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            result[0] += -9.027521336886584e-07;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -5.254698454085921e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8987185122361810441) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                        result[0] += -1.2722771712539146e-06;
                      } else {
                        result[0] += -1.2722771712539146e-06;
                      }
                    } else {
                      result[0] += -1.2722771712539146e-06;
                    }
                  } else {
                    result[0] += 3.606389999759268e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 1.8288652341548546e-06;
                } else {
                  result[0] += -1.6824842524791933e-06;
                }
              }
            } else {
              result[0] += -7.716058809415517e-06;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -1.2722771712539146e-06;
          } else {
            result[0] += -0.00010653084801159913;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -1.870225822219802e-06;
          } else {
            result[0] += -5.0261516174752496e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 7.101990172800806e-08;
          } else {
            result[0] += -0.0004422739210626994;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 7.976574287067991e-07;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 7.976574287067991e-07;
            } else {
              result[0] += 7.976574287067991e-07;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 7.976574287067991e-07;
            } else {
              result[0] += 7.976574287067991e-07;
            }
          }
        } else {
          result[0] += 7.976574287067991e-07;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 7.976574287067991e-07;
              } else {
                result[0] += 7.976574287067991e-07;
              }
            } else {
              result[0] += 7.976574287067991e-07;
            }
          } else {
            result[0] += 7.976574287067991e-07;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 7.976574287067991e-07;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 7.976574287067991e-07;
              } else {
                result[0] += 7.976574287067991e-07;
              }
            } else {
              result[0] += 7.976574287067991e-07;
            }
          }
        }
      } else {
        result[0] += 7.976574287067991e-07;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 5.022015749368229e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -1.1481310923511447e-06;
        } else {
          result[0] += -1.1481310923511447e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            result[0] += -8.646354336621028e-07;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -5.0328305047070655e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8987185122361810441) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                        result[0] += -1.2185580987906518e-06;
                      } else {
                        result[0] += -1.2185580987906518e-06;
                      }
                    } else {
                      result[0] += -1.2185580987906518e-06;
                    }
                  } else {
                    result[0] += 3.4541182070201736e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 1.751645469264882e-06;
                } else {
                  result[0] += -1.6114450988110097e-06;
                }
              }
            } else {
              result[0] += -7.390265396093842e-06;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -1.2185580987906518e-06;
          } else {
            result[0] += -0.00010203282000857541;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -1.7912596985350754e-06;
          } else {
            result[0] += -4.813933549705948e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 6.80212444122436e-08;
          } else {
            result[0] += -0.0004235998889013245;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 7.639781187424269e-07;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 7.639781187424269e-07;
            } else {
              result[0] += 7.639781187424269e-07;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 7.639781187424269e-07;
            } else {
              result[0] += 7.639781187424269e-07;
            }
          }
        } else {
          result[0] += 7.639781187424269e-07;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 7.639781187424269e-07;
              } else {
                result[0] += 7.639781187424269e-07;
              }
            } else {
              result[0] += 7.639781187424269e-07;
            }
          } else {
            result[0] += 7.639781187424269e-07;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 7.639781187424269e-07;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 7.639781187424269e-07;
              } else {
                result[0] += 7.639781187424269e-07;
              }
            } else {
              result[0] += 7.639781187424269e-07;
            }
          }
        }
      } else {
        result[0] += 7.639781187424269e-07;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 4.8099723094236454e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -1.0996538118175495e-06;
        } else {
          result[0] += -1.0996538118175495e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            result[0] += -8.281281264758961e-07;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -4.820330435786375e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                    result[0] += -1.1671071946255508e-06;
                  } else {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8987185122361810441) ) ) {
                      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.555383890033505745) ) ) {
                        result[0] += 3.308275751891691e-05;
                      } else {
                        result[0] += -0.0002488033412495676;
                      }
                    } else {
                      result[0] += 0.0012966386536342148;
                    }
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 1.6776861371166462e-06;
                } else {
                  result[0] += -1.5434054153289253e-06;
                }
              }
            } else {
              result[0] += -7.07822788468897e-06;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -1.1671071946255508e-06;
          } else {
            result[0] += -9.7724711228891e-05;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -1.7156277437061666e-06;
          } else {
            result[0] += -4.61067591761693e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 6.514919872897372e-08;
          } else {
            result[0] += -0.00040571432619418787;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 7.317208426946578e-07;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 7.317208426946578e-07;
            } else {
              result[0] += 7.317208426946578e-07;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 7.317208426946578e-07;
            } else {
              result[0] += 7.317208426946578e-07;
            }
          }
        } else {
          result[0] += 7.317208426946578e-07;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 7.317208426946578e-07;
              } else {
                result[0] += 7.317208426946578e-07;
              }
            } else {
              result[0] += 7.317208426946578e-07;
            }
          } else {
            result[0] += 7.317208426946578e-07;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 7.317208426946578e-07;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 7.317208426946578e-07;
              } else {
                result[0] += 7.317208426946578e-07;
              }
            } else {
              result[0] += 7.317208426946578e-07;
            }
          }
        }
      } else {
        result[0] += 7.317208426946578e-07;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 4.606881931894515e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -1.0532233765820097e-06;
        } else {
          result[0] += -1.0532233765820097e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.468148307738693481) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4558178340201005097) ) ) {
                result[0] += 3.179724569437655e-06;
              } else {
                result[0] += 0.00033432805207020297;
              }
            } else {
              result[0] += -1.1943436972866466e-05;
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -4.616802709417071e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    result[0] += -1.1178286903993888e-06;
                  } else {
                    result[0] += 3.1685911698998786e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 1.6068495731927982e-06;
                } else {
                  result[0] += -1.4782385560788035e-06;
                }
              }
            } else {
              result[0] += -6.779365462852299e-06;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -1.1178286903993888e-06;
          } else {
            result[0] += -9.359850275595035e-05;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -1.6431891798723883e-06;
          } else {
            result[0] += -4.416000386750508e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 6.23984187837547e-08;
          } else {
            result[0] += -0.0003885839415730999;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 7.008255583496064e-07;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 7.008255583496064e-07;
            } else {
              result[0] += 7.008255583496064e-07;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 7.008255583496064e-07;
            } else {
              result[0] += 7.008255583496064e-07;
            }
          }
        } else {
          result[0] += 7.008255583496064e-07;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 7.008255583496064e-07;
              } else {
                result[0] += 7.008255583496064e-07;
              }
            } else {
              result[0] += 7.008255583496064e-07;
            }
          } else {
            result[0] += 7.008255583496064e-07;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 7.008255583496064e-07;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 7.008255583496064e-07;
              } else {
                result[0] += 7.008255583496064e-07;
              }
            } else {
              result[0] += 7.008255583496064e-07;
            }
          }
        }
      } else {
        result[0] += 7.008255583496064e-07;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9189305784170854752) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
          result[0] += 4.412366593635195e-08;
        } else {
          result[0] += -1.0087533631565168e-06;
        }
      } else {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8168185667587940513) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)3.083217571286521075) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7847910031909549611) ) ) {
                    result[0] += 3.8620198482768456e-06;
                  } else {
                    result[0] += -2.073912785932719e-05;
                  }
                } else {
                  result[0] += -4.42186848840033e-05;
                }
              } else {
                result[0] += 5.976378440063996e-08;
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6828811456281408399) ) ) {
                if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                  result[0] += -1.5738091732049595e-06;
                } else {
                  result[0] += -4.2295445969795985e-05;
                }
              } else {
                result[0] += 1.3247242231660796e-07;
              }
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004060500000000000741) ) ) {
              result[0] += 0.0004986110934211542;
            } else {
              result[0] += 0.004746393226315816;
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                result[0] += -1.0706308613588057e-06;
              } else {
                result[0] += 0.0003167179087559679;
              }
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                  result[0] += 3.051248893869049e-05;
                } else {
                  result[0] += 1.5390039255539002e-06;
                }
              } else {
                result[0] += -1.4158232224501078e-06;
              }
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.22579873602455991) ) ) {
                result[0] += -0.0008634965362601751;
              } else {
                result[0] += -3.094166368976087e-05;
              }
            } else {
              result[0] += 0.0013321746805060322;
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -1.0706308613588057e-06;
      } else {
        result[0] += -9.655433346698238e-05;
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 6.712347586367104e-07;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            result[0] += 6.712347586367104e-07;
          } else {
            result[0] += 6.712347586367104e-07;
          }
        } else {
          result[0] += 6.712347586367104e-07;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 6.712347586367104e-07;
            } else {
              result[0] += 6.712347586367104e-07;
            }
          } else {
            result[0] += 6.712347586367104e-07;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 6.712347586367104e-07;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 6.712347586367104e-07;
              } else {
                result[0] += 6.712347586367104e-07;
              }
            } else {
              result[0] += 6.712347586367104e-07;
            }
          }
        }
      } else {
        result[0] += 6.712347586367104e-07;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 4.226064232693e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -9.661609970924655e-07;
        } else {
          result[0] += -9.661609970924655e-07;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
              result[0] += 3.53563453030149e-06;
            } else {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01173150000000000061) ) ) {
                result[0] += 2.1192929637400934e-05;
              } else {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
                  if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5008047942959380494) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.3644118032412060892) ) ) {
                      result[0] += -0.0003540738706385367;
                    } else {
                      result[0] += 1.5711763053712086e-06;
                    }
                  } else {
                    result[0] += -9.173693457543774e-05;
                  }
                } else {
                  result[0] += -1.2399582845580731e-05;
                }
              }
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -4.2351649310950576e-05;
                } else {
                  result[0] += -1.0254258556240444e-06;
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 1.4740229094152587e-06;
                } else {
                  result[0] += -1.3560432373962154e-06;
                }
              }
            } else {
              result[0] += -7.333390681017375e-06;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -1.0254258556240444e-06;
          } else {
            result[0] += -8.556972237778264e-05;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -1.5073585829334844e-06;
          } else {
            result[0] += -4.050961488027152e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 5.7240391591718705e-08;
          } else {
            result[0] += -0.0003721809076968432;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 6.428933645951696e-07;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 6.428933645951696e-07;
            } else {
              result[0] += 6.428933645951696e-07;
            }
          } else {
            result[0] += 6.428933645951696e-07;
          }
        } else {
          result[0] += 6.428933645951696e-07;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 6.428933645951696e-07;
            } else {
              result[0] += 6.428933645951696e-07;
            }
          } else {
            result[0] += 6.428933645951696e-07;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 6.428933645951696e-07;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 6.428933645951696e-07;
              } else {
                result[0] += 6.428933645951696e-07;
              }
            } else {
              result[0] += 6.428933645951696e-07;
            }
          }
        }
      } else {
        result[0] += 6.428933645951696e-07;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 4.047628074375117e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -9.253669989082316e-07;
        } else {
          result[0] += -9.253669989082316e-07;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            result[0] += -1.3082404046125474e-06;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -4.056344516041049e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                    result[0] += -9.82129530665481e-07;
                  } else {
                    result[0] += -0.0001096306848587905;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 1.4117855720862023e-06;
                } else {
                  result[0] += -1.298787329187778e-06;
                }
              }
            } else {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.394135022639764854) ) ) {
                result[0] += -0.0006598429855956511;
              } else {
                if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.625000000000000111) ) ) {
                  result[0] += 0.00027738465877507235;
                } else {
                  result[0] += -0.000299829649990565;
                }
              }
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -9.82129530665481e-07;
          } else {
            result[0] += -8.195673126159162e-05;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -1.443713720969232e-06;
          } else {
            result[0] += -3.879918653464032e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 5.48235434290573e-08;
          } else {
            result[0] += -0.00035646639705266874;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 6.157486228546094e-07;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 6.157486228546094e-07;
            } else {
              result[0] += 6.157486228546094e-07;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 6.157486228546094e-07;
            } else {
              result[0] += 6.157486228546094e-07;
            }
          }
        } else {
          result[0] += 6.157486228546094e-07;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 6.157486228546094e-07;
              } else {
                result[0] += 6.157486228546094e-07;
              }
            } else {
              result[0] += 6.157486228546094e-07;
            }
          } else {
            result[0] += 6.157486228546094e-07;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 6.157486228546094e-07;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 6.157486228546094e-07;
              } else {
                result[0] += 6.157486228546094e-07;
              }
            } else {
              result[0] += 6.157486228546094e-07;
            }
          }
        }
      } else {
        result[0] += 6.157486228546094e-07;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 3.876725985785793e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -8.862954365218424e-07;
        } else {
          result[0] += -8.862954365218424e-07;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5556488633165830304) ) ) {
              result[0] += 2.5904546105328396e-05;
            } else {
              result[0] += -1.6353869109016418e-05;
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -3.885074395098449e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
                    result[0] += -9.406612966845696e-07;
                  } else {
                    result[0] += 2.1647543695476195e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 1.3521760678342771e-06;
                } else {
                  result[0] += -1.243948924296615e-06;
                }
              }
            } else {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.394135022639764854) ) ) {
                result[0] += -0.0006319825838227779;
              } else {
                result[0] += 0.00010757059450004112;
              }
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -9.406612966845696e-07;
          } else {
            result[0] += -7.849629065559142e-05;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -1.382756121677784e-06;
          } else {
            result[0] += -3.716097721982897e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 5.250874130205237e-08;
          } else {
            result[0] += -0.00034141539665224677;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 5.897500074284017e-07;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 5.897500074284017e-07;
            } else {
              result[0] += 5.897500074284017e-07;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 5.897500074284017e-07;
            } else {
              result[0] += 5.897500074284017e-07;
            }
          }
        } else {
          result[0] += 5.897500074284017e-07;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 5.897500074284017e-07;
              } else {
                result[0] += 5.897500074284017e-07;
              }
            } else {
              result[0] += 5.897500074284017e-07;
            }
          } else {
            result[0] += 5.897500074284017e-07;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 5.897500074284017e-07;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 5.897500074284017e-07;
              } else {
                result[0] += 5.897500074284017e-07;
              }
            } else {
              result[0] += 5.897500074284017e-07;
            }
          }
        }
      } else {
        result[0] += 5.897500074284017e-07;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 3.713039857595945e-08;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -8.488735839145146e-07;
        } else {
          result[0] += -8.488735839145146e-07;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
              result[0] += 3.008408656315821e-06;
            } else {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01173150000000000061) ) ) {
                result[0] += 1.925958106623735e-05;
              } else {
                result[0] += -1.6655239139729465e-05;
              }
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -3.721035773899446e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                    result[0] += -9.009439666076785e-07;
                  } else {
                    result[0] += -0.00010543892415869388;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 1.2950834422553004e-06;
                } else {
                  result[0] += -1.1914259490246242e-06;
                }
              }
            } else {
              result[0] += -1.148216158230878e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -9.009439666076785e-07;
          } else {
            result[0] += -7.518195945394823e-05;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -1.3243723213725245e-06;
          } else {
            result[0] += -3.559193764796413e-05;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 5.029167654392293e-08;
          } else {
            result[0] += -0.0003269998912519888;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 5.648491256883866e-07;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 5.648491256883866e-07;
            } else {
              result[0] += 5.648491256883866e-07;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 5.648491256883866e-07;
            } else {
              result[0] += 5.648491256883866e-07;
            }
          }
        } else {
          result[0] += 5.648491256883866e-07;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                result[0] += 5.648491256883866e-07;
              } else {
                result[0] += 5.648491256883866e-07;
              }
            } else {
              result[0] += 5.648491256883866e-07;
            }
          } else {
            result[0] += 5.648491256883866e-07;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 5.648491256883866e-07;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 5.648491256883866e-07;
              } else {
                result[0] += 5.648491256883866e-07;
              }
            } else {
              result[0] += 5.648491256883866e-07;
            }
          }
        }
      } else {
        result[0] += 5.648491256883866e-07;
      }
    }
  }
}

